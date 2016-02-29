#define inPin A0
void setup() {
  pinMode(inPin,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
}


void loop() {
  int i = analogRead(inPin);
  if(i>663)
  Serial.println(i);
}
