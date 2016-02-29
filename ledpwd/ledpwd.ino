int r = 11
int g = 10;
int y = 9;


void setup() {
  Serial.begin(9600);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(y,OUTPUT);
}

void loop() {
  val = analogRead(potpin);
  Serial.println(val);
  analogWrite(ledpin,val/4);
  delay(10);
}
