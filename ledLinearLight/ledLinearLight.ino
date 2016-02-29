#define RPIN 3
#define GPIN 5
#define BPIN 6
void setup() {
  // put your setup code here, to run once:
  pinMode(RPIN,OUTPUT);
  pinMode(GPIN,OUTPUT);
  pinMode(BPIN,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);
}

void Update(int r,int g,int b){
  analogWrite(RPIN,r);
  analogWrite(GPIN,g);
  analogWrite(BPIN,b);
}

int state = 0;
unsigned char counter= 0;
char dx = 1;
void loop() {
  int colors[4] = {0,0,0,0}, phase = state & 0xff;
  int power = ((state & 0x100) ? 0xff-phase : phase);
  colors[state / 512] = 255.0 * pow(power / 256.0,2);
  if(colors[3]){int d = colors[3];colors[0]=d*30/100;colors[1]=d*59/100;colors[2]=d*14/100;}
  Update(colors[0],colors[1],colors[2]);
  if(++state == 512*4) state = 0;
  analogWrite(9,counter);
  counter +=dx;
  if(counter==0 || counter==256) dx = -dx;
  delay(2);
}
