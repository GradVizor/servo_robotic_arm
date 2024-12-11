// #define   MotorEN    13 
// #define   MotorTA    12
// #define   MotorTB    14

#define   MotorEN    26 
#define   MotorTA    25
#define   MotorTB    33


void setup() {
  pinMode(MotorEN, OUTPUT);
  pinMode(MotorTA, OUTPUT);
  pinMode(MotorTB, OUTPUT);
}

void loop() {
  Clockwise(200);
  delay(1000);
  CounterClockwise(200);
  delay(1000);  
}

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
