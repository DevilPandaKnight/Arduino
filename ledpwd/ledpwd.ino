int r = 9;
int g = 10;
int y = 11;

void setup() {
  Serial.begin(9600);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(y,OUTPUT);
}

int i = 0;
void loop() {
  for (int i = 0;i<255;i++){
    analogWrite(r,i);
    delay(5);
  }
}
