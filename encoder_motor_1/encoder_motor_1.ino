#include <PIDController.h>

#define   MotorEN    13 
#define   MotorTA    12
#define   MotorTB    14
#define   EncA       25
#define   EncB       26
#define   CountPerRev   810

PIDController pos_pid;
unsigned long currentMillis;
unsigned long previousArmMillis;
unsigned long previousMillis;

volatile long encoder_pos = 0;    // encoder 1


void setup() {
  Serial.begin(9600);
  pinMode(MotorEN, OUTPUT);
  pinMode(MotorTA, OUTPUT);
  pinMode(MotorTB, OUTPUT);
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);
  attachInterrupt(digitalPinToInterrupt(EncA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EncB), doEncoderB, CHANGE); 

   // Initialize PID controller
  pos_pid.begin();
  pos_pid.tune(10, 0.0, 0.0); // Start with smaller PID values for fine-tuning
  pos_pid.limit(-255, 255);     // PID output range
  Serial.println("System Initialized. Enter degree (0-360) to move motor.");

}


void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read the input as a string
    int set_pos = input.toInt(); // Convert the string to an integer
    if (set_pos >= 0 && set_pos <= 360) {
      float mapped_set_pos = map(set_pos, 0, 360, 0, CountPerRev);
      pos_pid.setpoint((float)mapped_set_pos); // Set the PID target position
      // Serial.print("Set Position: ");
      // Serial.println(set_pos);
    } else {
      Serial.println("Invalid input! Enter a value between 0 and 360.");
    }
  }
  // Compute the PID output
  float pid_output = pos_pid.compute(encoder_pos);
  int motor_power = abs((int)pid_output); // Motor power should be positive

  // Determine motor direction and apply power
  if (pid_output > 0) {
    Clockwise(motor_power);
  } else if (pid_output < 0) {
    CounterClockwise(motor_power);
  } else {
    Stop();  // Stop the motor if the output is zero
  }

}

// ************ Motor Controls ****************
void Clockwise(int power){
  digitalWrite(MotorTA, HIGH);
  digitalWrite(MotorTB, LOW);
  analogWrite(MotorEN, power);
}

void CounterClockwise(int power){
  digitalWrite(MotorTA, LOW);
  digitalWrite(MotorTB, HIGH);
  analogWrite(MotorEN, power);
}

void Stop(){
  digitalWrite(MotorTA, LOW);
  digitalWrite(MotorTB, LOW);
  analogWrite(MotorEN, 0);
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