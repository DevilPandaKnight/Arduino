#define RED 3
#define GREEN 4
#define R 9
#define G 10
#define B 5
#define IN1 15
#define IN2 16
#define IN3 17
#define p(msg) Serial.println(msg);

void setup(){
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(IN1,INPUT);
  pinMode(IN2,INPUT);
  pinMode(IN3,INPUT);
  Serial.begin(9600);
  analogWriteResolution(10);
}


int selectLED()
{
  int i = random()%5+3;
  if (i==7){return R;}
  return i;
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
  }
  analogWrite(light,0);
  return 0;
}

void loop(){
  //fadeLight(selectLED());
  float in1 = analogRead(IN1);
  float in2 = analogRead(IN2);
  analogWrite(R,1024-in1);
  analogWrite(G,1024-in2);
  p("---------------------");
  p(in1);
  p(in2);
  p("---------------------");
  //delay(300);
}
