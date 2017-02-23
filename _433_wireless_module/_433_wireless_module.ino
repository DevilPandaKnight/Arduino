void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0;i<1024;i++){
    analogWrite(3,i);
    delay(5);
    Serial.print("write:");
    Serial.println(i);
    Serial.println(analogRead(A0));
    Serial.println(analogRead(A1));
    Serial.println("-----------------------------------------------");
    delay(200);
  }
}
