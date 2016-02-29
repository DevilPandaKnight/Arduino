#include <SoftwareSerial.h>
#include "Buttons.h"
//定义12个按钮
#define b1 A0
#define b2 A1
#define b3 A2
#define b4 A3
#define b5 A4
#define b6 A5
#define b7 2
#define b8 3
#define b9 4
#define b10 5
#define b11 6
#define b12 7
SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
Buttons buttons;
//把每个按钮注册到button类里面, 当按下按钮时调用对应的函数
void setup() {
  buttons.addButton(b1,b1Action);
  buttons.addButton(b2,b2Action);
  buttons.addButton(b3,b3Action);
  buttons.addButton(b4,b4Action);
  buttons.addButton(b5,b5Action);
  buttons.addButton(b6,b6Action);
  buttons.addButton(b7,b7Action);
  buttons.addButton(b8,b8Action);
  buttons.addButton(b9,b9Action);
  buttons.addButton(b10,b10Action);
  buttons.addButton(b11,b11Action);
  buttons.addButton(b12,b12Action);
  Serial.begin(9600);
  BT.begin(31250);
}

void b1Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,60,127);
  }
  else if(s == falling){
    stopNote(0x90,60,0);
  }
}

void b2Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,62,127);
  }
  else if(s == falling){
    stopNote(0x90,62,0);
  }
}

void b3Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,64,127);
  }
  else if(s == falling){
    stopNote(0x90,64,0);
  }
}

void b4Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,65,127);
  }
  else if(s == falling){
    stopNote(0x90,65,0);
  }
}

void b5Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,67,127);
  }
  else if(s == falling){
    stopNote(0x90,67,0);
  }
}

void b6Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,69,127);
  }
  else if(s == falling){
    stopNote(0x90,69,0);
  }
}

void b7Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,71,127);
  }
  else if(s == falling){
    stopNote(0x90,71,0);
  }
}

void b8Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x90,72,127);
  }
  else if(s == falling){
    stopNote(0x90,72,0);
  }
}

void b9Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x91,30,127);
  }
  else if(s == falling){
    stopNote(0x91,30,0);
  }
}

void b10Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x91,45,127);
  }
  else if(s == falling){
    stopNote(0x91,45,0);
  }
}

void b11Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x91,55,127);
  }
  else if(s == falling){
    stopNote(0x91,55,0);
  }
}

void b12Action(unsigned char b, state s){
  if(s == rising){
    sendNote(0x91,65,127);
  }
  else if(s == falling){
    stopNote(0x91,65,0);
  }
}



//channel 一共有16个,对应16种在logic pro 里的乐器
//note是音符
//velocity是按键的音量
void sendNote(int channel,int note,int velocity){
  BT.write(channel);
  BT.write(note);
  BT.write(velocity);
  
}

void stopNote(int channel,int note,int velocity){
  BT.write(channel);
  BT.write(note);
  BT.write(velocity);
  Serial.println(note);
}

//开始程序
void loop(){
  buttons.begin();
}

