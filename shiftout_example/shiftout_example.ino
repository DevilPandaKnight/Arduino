#include <SoftwareSerial.h>
//SoftwareSerial BT(9, 10); // RX, TX
int data = 11;
int clock_ = 12;
int latch = 8;

void setup() {
 Serial.begin(9600);
 pinMode(data,OUTPUT);
 pinMode(clock_,OUTPUT);
 pinMode(latch,OUTPUT);
}


void loop() {
  Serial.println(analogRead(A5));
  delay(5);
  digitalWrite(latch, LOW);
  shiftOut(data, clock_, MSBFIRST, 0b0101);
  digitalWrite(latch, HIGH);
}
