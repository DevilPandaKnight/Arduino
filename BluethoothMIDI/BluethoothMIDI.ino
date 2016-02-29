#include <SoftwareSerial.h>
#define NOTEOFF 0B10000000 //note off
#define NOTEON 0B10010000 // note on
#define AFTERTOUCH 0B10100000 // aftertouch
#define CC 0B10110000 // continuous controller
#define PC 0B11000000 // patch change
#define CP 0B11010000 // channel pressure
#define PB 0B11100000 // pitch bend
#define NMC 0B11110000 // non-musical commands

enum state{
  low=0,
  high,
  rising,
  falling
};
SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
                 //1 ,+ ,2 ,0
char buttons[4] = {12,A4,A3,A2};
char bValue[4] = {0,0,0,0};
char bOldValue[4] = {0,0,0,0};
state bstate[4] = {low,low,low,low};

void setup() {
  Serial.begin(31250);   // 與電腦序列埠連線
  pinMode(7,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(12,INPUT);
  digitalWrite(12,LOW);
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(9600);
}

void readButton(){
  int val = 0;
  for(int i = 0;i<4;i++){
    val = digitalRead(buttons[i]);
    bValue[i]=val;
    if(val != bOldValue[i]){
      bstate[i] = (val>bOldValue[i])? rising:falling;
    }
    else{
      bstate[i] = val==0? low:high;
    }
    bOldValue[i] = val;
  }
}

void buttonAction(char button,state st,void (*action)()){
  for(int i = 0;i<4;i++){
    if(button == buttons[i] && st == bstate[i]){
      action();
    }
  }
}

void sendNote(){
  Serial.write(0x90);
  Serial.write(0x59);
  Serial.write(127);
  digitalWrite(7,HIGH);
}

void stopNote(){
  Serial.write(0x90);
  Serial.write(0x59);
  Serial.write((unsigned char)0);
  digitalWrite(7,LOW);
}


void loop() {
  readButton();
  buttonAction(12,low,sendNote);
  buttonAction(12,falling,stopNote);
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
  delay(1000);
}
