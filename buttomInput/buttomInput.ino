#include "Buttons.h"
Buttons b;
float speed = 0;
int count = 0;
void up(unsigned char button,state s){
  if (s==rising){
    speed++;
  }
  if(s == high){
    count++;
    if(count >= 10){
      speed++;
    }
    digitalWrite(13,HIGH);
  }
  if(s==falling){count = 0;digitalWrite(13,0);}
}

void down(unsigned char button,state s){
  if (s==rising){
    speed--;
  }
  if(s == high){
    count++;
    if(count >= 10){
      speed--;
    }
  }
  if(s==falling){count = 0;}
}

void setup() {
  b.addButton(9,down);
  b.addButton(12,up);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  b.begin();
  analogWrite(3,speed);
  Serial.print("speed = ");
  Serial.println(speed);
}
