void setup() {
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
}

void loop() {
//  digitalWrite(8,HIGH);
//  delay(300);
//  digitalWrite(8,LOW);
//  delay(100);
  digitalWrite(8,HIGH);
  delay(800);
  digitalWrite(8,LOW);
  delay(300);

  for (int i = 0;i<255;i++){
    analogWrite(9,i);
    delay(5);
  }
   for (int i = 255;i>=0;i--){
    analogWrite(9,i);
    delay(5);
  }
    
    
}
