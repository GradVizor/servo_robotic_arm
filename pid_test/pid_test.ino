#define p     32
#define i     33
#define d     34

void setup() {
  Serial.begin(9600);
  pinMode(p,INPUT);
  pinMode(i,INPUT);
  pinMode(d,INPUT);
}

void loop() {
  int p_val = analogRead(p);
  int i_val = analogRead(i);
  int d_val = analogRead(d);
  Serial.print(p_val);
  Serial.print(",");
  Serial.print(i_val);
  Serial.print(",");
  Serial.println(d_val);
}
