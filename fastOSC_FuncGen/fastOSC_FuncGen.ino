#include "OSC_FuncGen.hpp"
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

OSC_FuncGen s;
void setup() {
 Serial.begin(230400);
 pinMode(A0,INPUT);
 pinMode(2,OUTPUT);
}

void loop() {
  String str;
  int mode = 0;
  int d = 5;
  volatile unsigned short a;
  for (;;){
    if (Serial.available()){
      str = Serial.readStringUntil('\n');
      if (str=="1") mode = 1;//func generator
      else if(str=="0") mode = 0; //osc
      else d = str.toInt(); //set delay
    }
    if(mode){
      PIN2OFF;
      delayMicroseconds(d);
      PIN2ON;
      delayMicroseconds(d);
    }
    else{
      a = analogRead(A0);
      Serial.write((char*)&a,2);
    }
  }
}
