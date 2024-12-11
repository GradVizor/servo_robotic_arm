#include<Servo.h>
// Declaring Macros for control
#define open 104
#define closed 12

// Declare 6 servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Define servo pins
const int servoPin1 = 3;  
const int servoPin2 = 5;  
const int servoPin3 = 6;  
const int servoPin4 = 9;  
const int servoPin5 = 10;  
const int servoPin6 = 11;  

unsigned long previous = 0;

void pos_control(int p1, int p2, int p3, int p4, int p5, int p6){
  // Set the servo positions
  servo1.write(p1);
  servo2.write(p2);
  servo3.write(p3);
  servo4.write(p4);
  servo5.write(p5);
  servo6.write(p6);
  // unsigned long current = 0;
  // current = millis();
  // if ((current-previous) == 100){
  //   servo6.write(p6);
  //   previous = current;
  // } else if ((current-previous) == 200){
  //   servo5.write(p5);
  //   previous = current;
  // } else if ((current-previous) == 300){
  //   servo4.write(p4);
  //   previous = current;
  // } else if ((current-previous) == 400){
  //   servo3.write(p3);
  //   previous = current;
  // } else if ((current-previous) == 500){
  //   servo2.write(p2);
  //   previous = current;
  // } else if ((current-previous) == 600){
  //   servo1.write(p1);
  //   previous = current;
  // } 
}

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
  Serial.println("System Initialized. ");
  // pos_control(26, 70, 73, 69, 78, open);
}

void loop() {
  pos_control(26, 70, 73, 69, 78, open);
}
