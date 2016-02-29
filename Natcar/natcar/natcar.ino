#include <Servo.h>
#define SI 22
#define CK 23
#define AIN 21


Servo myServo;
int weight[128],values[128],left,right,mid,knowLeft=0,knowRight=0,degree=80;
double kp=60,ki=0,kd=40,error=0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(AIN,INPUT);
  pinMode(SI,OUTPUT);
  pinMode(CK,OUTPUT);
  myServo.attach(9);
}

void sample(){
  digitalWrite(SI,HIGH);
  delayMicroseconds(20);
  digitalWrite(CK,HIGH);
  delayMicroseconds(20);
  digitalWrite(SI,LOW);
  delayMicroseconds(20);
  digitalWrite(CK,LOW);
  for(int i = 0;i<128;i++){
    digitalWrite(CK,HIGH);
    values[i] = analogRead(AIN);
    digitalWrite(CK,LOW);
  }
    digitalWrite(CK,HIGH);
    digitalWrite(CK,LOW);
}



void printLine(){
  sample();
  delay(20);
  sample();
  knowLeft=0;
  knowRight=0;
  for(int i = 0;i<128;i++){
    weight[i] = values[i]/1023.0*9;
  }
  for(int i = 9;i>0;i--){
    for(int j = 0;j<128;j++){
      if(weight[j]>=i){
        if(i>0){Serial.print(weight[j]);}
        else{Serial.print("0");}
      }
      else{
        Serial.print(" ");
      }
    }
    Serial.println();
  }
  for(int i = 0;i<128;i++){
    if(weight[i]==7 && !knowLeft){left = i;knowLeft=1;}
    Serial.print(weight[i]);
  }
  Serial.println("\n");
  for(int i = 127;i>=0;i--){
    if(weight[i]==7 && !knowRight){right = i;knowRight=1;}
  }
  mid = (right-left)/2+left;
  for(int i = 0;i<128;i++){
    if(i==left || i == right){
      Serial.print("|");
    }
    else if(i==mid){
      Serial.print("*");
    }
    else{
      Serial.print(".");
    }
  }
  Serial.println("\n\n");
}

void pidControl(){
 int realMid = 64;
 int lastErr = error;
 error = (mid - realMid)/64.0;
 int p = kp*error;
 //ki += error*2;
 int d = (lastErr - error)*kd;
 
 int out = degree-(p+ki+d);
 if(out>120){out=120;}
 if(out<50){out=50;}
 Serial.println(out);
 myServo.write(out);
 delay(15);
}

void loop() {
  printLine();
  pidControl();
}
