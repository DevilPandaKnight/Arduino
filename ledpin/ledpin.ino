int ledpin = 13;
int val;


void setup() {
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  
}

void loop() {
  val = Serial.read();
  if(val=='r'){
    digitalWrite(ledpin,HIGH);

    Serial.println("hello world.");
  }
  
  if(val == 's'){
    digitalWrite(ledpin,LOW);
    Serial.println("Good Bye world.");
  }
}
