#include <LiquidCrystal.h>
                //rs rw  E D0~~~~~~~~~~~D7 
LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);
char s[100];
#define B1 A5

void setString(char* str){
  int i = 0;
  while(str[i] != '\0'){
    s[i]=str[i];
    i++;
  }
  s[i]='\0';
}

void setup() {
  // put your setup code here, to run once:
  pinMode(B1,INPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  setString("hello world");
  lcd.print(s);
  lcd.setCursor(0,2);
  //lcd.print("Arduion is fun");
  Serial.begin(9600);
}
int count = 0;
int lastCount = -1;
bool beginTypeing = false;
char buff[100];
void loop() {
  if (Serial.available()){
    if(!beginTypeing) lastCount = 0;
    char c = Serial.read();
    Serial.println(c);
    buff[count] = c;
    count++;
    beginTypeing = true;
  }
  /*if(digitalRead(B1)){
    if(!beginTypeing){ 
      lastCount = 0;
      char c = '1';
      buff[count] = c;
      count++;
      beginTypeing = true;
      Serial.println("inputting.");
    }
  }*/
  if(count==lastCount){
    beginTypeing = false;
    buff[count]='\0';
    setString(buff);
    lcd.clear();
    lcd.print(s);
    count=0;
    memset(buff,100,0);
    Serial.println("in printing.");
  }
  if(!beginTypeing){if(lastCount != -1)lastCount = -1;}
  else{lastCount++;}
  // put your main code here, to run repeatedly:
  //lcd.scrollDisplayLeft();
  delay(1);
}
