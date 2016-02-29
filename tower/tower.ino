#include <Servo.h>
Servo myservo;

void setup(){
  myservo.attach(9);
}

int i = 0;
int di = 1;
void loop(){
  myservo.write(i);
  i = i+di;
  if(i == 180){di = -1;}
  if(i == 0){di = 1;}
  delay(2);
}
































































//void servopulse(int servopin,int myangle){
//  pulsewidth = (myangle*11)+500;
//  digitalWrite(servopin,HIGH);
//  delayMicroseconds(pulsewidth);
//  digitalWrite(servopin,LOW);
//  delay(20-pulsewidth/1000);
//}
//
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(servopin,OUTPUT);
//  Serial.begin(9600);
//  Serial.println("servo=o_seral_simple ready.");
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////  val = Serial.read();
////  if(val >'0' && val <='9'){
////    val = val-'0';
////    val = val*(180/9);
////    Serial.print("moving servo to");
////    Serial.print(val,DEC);
////    Serial.println();
////    for(int i = 0;i<=50;i++){
////      servopulse(servopin,val);
////    }
////  }
// 
//  digitalWrite(servopin,HIGH);
//  delayMicroseconds(1000);
//  digitalWrite(servopin,LOW);
//  delay(400);
//}
