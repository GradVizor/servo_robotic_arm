#include <Servo.h>

// Declaring Macros for control
#define OPEN 104
#define CLOSED 12

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

// Variables to track positions and timing
unsigned long previousMillis = 0;
unsigned long trajectoryMillis = 0;
const unsigned long interval = 15; // Update interval for smooth movement (20ms)
const unsigned long interval2 = 1500; // Update interval for trajectory (1s)
int currentPos1 = 0, currentPos2 = 0, currentPos3 = 0, currentPos4 = 0, currentPos5 = 0, currentPos6 = 0;
int targetPos1, targetPos2, targetPos3, targetPos4, targetPos5, targetPos6;

// Function to move servos smoothly
void moveServoSmoothly() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (currentPos1 < targetPos1) currentPos1++;
    if (currentPos1 > targetPos1) currentPos1--;

    if (currentPos2 < targetPos2) currentPos2++;
    if (currentPos2 > targetPos2) currentPos2--;

    if (currentPos3 < targetPos3) currentPos3++;
    if (currentPos3 > targetPos3) currentPos3--;

    if (currentPos4 < targetPos4) currentPos4++;
    if (currentPos4 > targetPos4) currentPos4--;

    if (currentPos5 < targetPos5) currentPos5++;
    if (currentPos5 > targetPos5) currentPos5--;

    if (currentPos6 < targetPos6) currentPos6++;
    if (currentPos6 > targetPos6) currentPos6--;

    servo1.write(currentPos1);
    servo2.write(currentPos2);
    servo3.write(currentPos3);
    servo4.write(currentPos4);
    servo5.write(currentPos5);
    servo6.write(currentPos6);
  }
}

// Function to set target positions for servos
void pos_control(int p1, int p2, int p3, int p4, int p5, int p6) {
  targetPos1 = p1;
  targetPos2 = p2;
  targetPos3 = p3;
  targetPos4 = p4;
  targetPos5 = p5;
  targetPos6 = p6;
}

// Hard-coded trajectory function
void trajectory() {
  unsigned long currentMillis = millis();
  if (currentMillis - trajectoryMillis >= interval2) {
    trajectoryMillis = currentMillis;

    static int step = 0; // Step variable to keep track of trajectory steps

    switch (step) {
      case 0:
        pos_control(29, 58, 135, 23, 78, OPEN); // P1
        break;
      case 1:
        pos_control(29, 58, 150, 23, 78, OPEN); // P1
        break;
      case 2:
        pos_control(29, 58, 150, 23, 89, CLOSED); // P2
        break;
      case 3:
        pos_control(74, 58, 110, 23, 89, CLOSED); // P3
        break;
      case 4:
        pos_control(74, 41, 130, 23, 89, OPEN); // P4
      default:
        step = -1; // Reset to -1 to start over or modify for different behaviors
        break;
    }

    step++; // Move to the next step
  }
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
  Serial.println("System Initialized.");

  // Set initial position
  pos_control(26, 70, 73, 69, 60, OPEN);
}

void loop() {
  moveServoSmoothly(); // Update servo positions incrementally
  trajectory(); // Run trajectory function
}
