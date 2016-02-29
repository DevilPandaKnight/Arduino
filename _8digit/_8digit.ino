#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8
#define SEG_H 9

#define COM1 10
#define COM2 11
#define COM3 12
#define COM4 13


unsigned char table[10][8] = {{0,0,1,1,1,1,1,1}, //0 
                              {0,0,0,0,0,1,1,0}, //1 
                              {0,1,0,1,1,0,1,1}, //2 
                              {0,1,0,0,1,1,1,1}, //3 
                              {0,1,1,0,0,1,1,0}, //4 
                              {0,1,1,0,1,1,0,1}, //5
                              {0,1,1,1,1,1,0,1}, //6
                              {0,0,0,0,0,1,1,1}, //7
                              {0,1,1,1,1,1,1,1}, //8
                              {0,1,1,0,1,1,1,1}  //9
                              }; 

void setup() {
  for(int i = 2;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
}

void displayNumber(int n){
  if(n<0 || n>9999){return;}
  int thousand = n/1000;
  int hundred = (n%1000)/100;
  int tenth = (n%100)/10;
  int single = n%10;
  Display(1,single);
  Display(2,tenth);
  Display(3,hundred);
  Display(4,thousand);
//  Serial.print(thousand);
//  Serial.print(hundred);
//  Serial.print(tenth);
//  Serial.println(single);
}
int i = 0;
void loop() {
//  Display(1,1);
//  delay(500);
//  Display(2,2);
//  delay(500);
//  Display(3,3);
//  delay(500);
//  Display(4,4);
//  delay(500);

  
  if(i == 9999){
    displayNumber(9999);
  }
  else{
    displayNumber(i++);
  }
}


void Display(unsigned char com,unsigned char num){
  for(int i = 2;i<=9;i++){
    digitalWrite(i,LOW);
  }
  
  switch(com){
    case 1:
      digitalWrite(COM1,LOW);
      digitalWrite(COM2,HIGH);
      digitalWrite(COM3,HIGH);
      digitalWrite(COM4,HIGH);
      break;
    case 2:
      digitalWrite(COM1,HIGH);
      digitalWrite(COM2,LOW);
      digitalWrite(COM3,HIGH);
      digitalWrite(COM4,HIGH);
      break;
    case 3:
      digitalWrite(COM1,HIGH);
      digitalWrite(COM2,HIGH);
      digitalWrite(COM3,LOW);
      digitalWrite(COM4,HIGH);
      break;
    case 4:
      digitalWrite(COM1,HIGH);
      digitalWrite(COM2,HIGH);
      digitalWrite(COM3,HIGH);
      digitalWrite(COM4,LOW);
      break;
    default:break;
  }
  digitalWrite(SEG_A,table[num][7]);
  digitalWrite(SEG_B,table[num][6]);
  digitalWrite(SEG_C,table[num][5]);
  digitalWrite(SEG_D,table[num][4]);
  digitalWrite(SEG_E,table[num][3]);
  digitalWrite(SEG_F,table[num][2]);
  digitalWrite(SEG_G,table[num][1]);
  digitalWrite(SEG_H,table[num][0]);
}
