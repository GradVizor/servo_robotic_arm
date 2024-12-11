#include <PIDController.h>

#define MotorEN 13
#define MotorTA 12
#define MotorTB 14
#define EncA 25
#define EncB 26

#define p    32
#define i    33
#define d    34

#define CountPerRev 810

PIDController pos_pid;
volatile long encoder_pos = 0; // encoder position

int p_val, i_val, d_val; 

void setup() {
  Serial.begin(9600);
  
  pinMode(MotorEN, OUTPUT);
  pinMode(MotorTA, OUTPUT);
  pinMode(MotorTB, OUTPUT);
  pinMode(p, INPUT);
  pinMode(i, INPUT);
  pinMode(d, INPUT);
  pinMode(EncA, INPUT_PULLUP); // Use INPUT_PULLUP to reduce noise
  pinMode(EncB, INPUT_PULLUP);
  
  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(EncA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EncB), doEncoderB, CHANGE);
  
  // Initialize PID controller
  pos_pid.begin();
  // pos_pid.tune(0.02*p_val, 0.01*i_val, 0.01*d_val); // Adjust these values as necessary
  // pos_pid.tune(15, 0, 2000);
  pos_pid.limit(-255, 255);

  // p_val = analogRead(p);
  // i_val = analogRead(i);
  // d_val = analogRead(d);
  
  Serial.println("System Initialized. Enter degree (0-360) to move motor.");
}

void loop() {
  p_val = analogRead(p);
  i_val = analogRead(i);
  d_val = analogRead(d);
  pos_pid.tune(0.05*p_val, 0.001*i_val, 1*d_val); // Adjust these values as necessary
  // pos_pid.tune(27.35, 0.25, 12.8);
  pos_pid.limit(-255, 255);
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int set_pos = input.toInt();
    if (set_pos >= 0 && set_pos <= 360) {
      float mapped_set_pos = map(set_pos, 0, 360, 0, CountPerRev);
      pos_pid.setpoint(mapped_set_pos);
    } else {
      Serial.println("Invalid input! Enter a value between 0 and 360.");
    }
  }
  
  // Compute the PID output
  float pid_output = pos_pid.compute(encoder_pos);
  int motor_power = constrain(abs((int)pid_output), 0, 255); // Constrain motor power

  // Determine motor direction and apply power
  if (pid_output > 0) {
    Clockwise(motor_power);
  } else if (pid_output < 0) {
    CounterClockwise(motor_power);
  } else {
    Stop(); // Stop the motor if the output is zero
  }

  // Debugging outputs
  Serial.print("Encoder Position: ");
  Serial.println(encoder_pos);
  Serial.print("PID Output: ");
  Serial.println(pid_output);
  Serial.print("Motor Power: ");
  Serial.println(motor_power);
}

void Clockwise(int power) {
  digitalWrite(MotorTA, HIGH);
  digitalWrite(MotorTB, LOW);
  analogWrite(MotorEN, power); // Use PWM on channel 0
}

void CounterClockwise(int power) {
  digitalWrite(MotorTA, LOW);
  digitalWrite(MotorTB, HIGH);
  analogWrite(MotorEN, power); // Use PWM on channel 0
}

void Stop() {
  digitalWrite(MotorTA, LOW);
  digitalWrite(MotorTB, LOW);
  analogWrite(MotorEN, 0); // Stop PWM on channel 0
}

// ************** encoder 1 *******************
void doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(EncA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(EncB) == LOW) {  
      encoder_pos = encoder_pos + 1;         // CW
    } 
    else {
      encoder_pos = encoder_pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(EncB) == HIGH) {   
      encoder_pos = encoder_pos + 1;          // CW
    } 
    else {
      encoder_pos = encoder_pos - 1;          // CCW
    }
  }
}

void doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(EncB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(EncA) == HIGH) {  
      encoder_pos = encoder_pos + 1;         // CW
    } 
    else {
      encoder_pos = encoder_pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(EncA) == LOW) {   
      encoder_pos = encoder_pos + 1;          // CW
    } 
    else {
      encoder_pos = encoder_pos - 1;          // CCW
    }
  }
}