#include<Servo.h>
// Declare 6 servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Define potentiometer pins (assuming external ADC)
const int potPin1 = A0;  // Modify according to external ADC setup
const int potPin2 = A1;  // Analog pins for potentiometers
const int potPin3 = A2;
const int potPin4 = A3;
const int potPin5 = A4;
const int potPin6 = A5;

// Define servo pins
const int servoPin1 = 3;  // GPIO 5
const int servoPin2 = 5;  // GPIO 4
const int servoPin3 = 6;  // GPIO 0
const int servoPin4 = 9;  // GPIO 2
const int servoPin5 = 10;  // GPIO 14
const int servoPin6 = 11;  // GPIO 12

// void pos_control(int p1, int p2, int p3, int p4, int p5){
  
// }

void setup() {
  // Attach the servos to the pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer values and map them to servo angles (0-180 degrees)
  int potValue1 = analogRead(potPin1);
  int potValue2 = analogRead(potPin2);
  int potValue3 = analogRead(potPin3);
  int potValue4 = analogRead(potPin4);
  int potValue5 = analogRead(potPin5);
  int potValue6 = analogRead(potPin6);

  // Map the potentiometer values (0-1023) to servo angles (0-180)
  int angle1 = map(potValue1, 0, 1023, 0, 180);
  int angle2 = map(potValue2, 0, 1023, 0, 180);
  int angle3 = map(potValue3, 0, 1023, 0, 180);
  int angle4 = map(potValue4, 0, 1023, 0, 180);
  int angle5 = map(potValue5, 0, 1023, 0, 180);
  int angle6 = map(potValue6, 0, 1023, 0, 180);

  // Set the servo positions
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);
  servo5.write(angle5);
  servo6.write(angle6);

  Serial.print(angle1);
  Serial.print(",");
  Serial.print(angle2);
  Serial.print(",");
  Serial.print(angle3);
  Serial.print(",");
  Serial.print(angle4);
  Serial.print(",");
  Serial.print(angle5);
  Serial.print(",");
  Serial.println(angle6);

  // Delay to allow the servos to move smoothly
  delay(15);
}
