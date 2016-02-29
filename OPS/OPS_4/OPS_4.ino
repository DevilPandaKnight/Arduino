#define RED 3
#define GREEN 4
#define R 9
#define G 6
#define B 5
#define SPEAKER 10
#define IN1 17
#define IN2 18
#define IN3 19
#define p(msg) Serial.println(msg);


const float INITIAL_TIME = 10000;
const float DECREASE_RATE = 1;

void playBuzzer(int val, int time)
{
 for (int i = 0; i < time; i++)
 {
   digitalWrite(SPEAKER,127);
   delayMicroseconds(val);
   digitalWrite(SPEAKER,0);    
   delayMicroseconds(900);
 }
}


int selectLED()
{
  int i = random()%5+3;
  if (i==7){return R;}
  return i;
}


void setup(){
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(SPEAKER,OUTPUT);
  pinMode(IN1,INPUT);
  pinMode(IN2,INPUT);
  pinMode(IN3,INPUT);
  Serial.begin(9600);
}

int buttonPressed(){
  float in1 = analogRead(IN1);
  float in2 = analogRead(IN2);
  float in3 = analogRead(IN3);
  if (in1 > 100){return IN1;}
  if(in2>100) {return IN2;}
  if(in3>100){return IN3;}
  return 0;
}

void allLightOff(){
  analogWrite(RED,0);
  analogWrite(GREEN,0);
  analogWrite(R,0);
  analogWrite(G,0);
  analogWrite(B,0);
}

int fadeLight(int light){
  int t = random()%256;
  allLightOff();
  for(int i = t;i>0;i--){
    analogWrite(light,i);
    delay(10);
    if (buttonPressed()){
      analogWrite(light,0);
      return 1;
    }
  }
  analogWrite(light,0);
  return 0;
}

void loop(){
  float in1 = analogRead(IN1);
  float in2 = analogRead(IN2);
  float in3 = analogRead(IN3);
  int b = 0;
  while(true){
    b = buttonPressed();
    if(b){allLightOff();break;}
    fadeLight(selectLED());
  }
  
  float totalTime = INITIAL_TIME;
  float timeLeft = totalTime;
  int litLED = selectLED();
  
  while (timeLeft > 0){
    b = buttonPressed();
    digitalWrite(litLED,HIGH);
    if((b==IN1 && (litLED==R || litLED==B || litLED==G)) || (b==IN2 && litLED==RED) || (b==IN3 && litLED==GREEN)){
      digitalWrite(litLED,LOW);
      p("in loop");
      playBuzzer(1000,30);
      litLED = selectLED();
      totalTime-=DECREASE_RATE;
      timeLeft = totalTime;
      continue;
    }
    delayMicroseconds(150);
    timeLeft--;
  }
allLightOff();
analogWrite(SPEAKER,255);
delay(2000);
  analogWrite(SPEAKER,0);
}
