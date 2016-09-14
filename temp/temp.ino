//SoftwareSerial BT(9, 10); // RX, TX
int data = 11;
int clock_ = 12;
int latch = 8;

void setup() {
 Serial.begin(9600);
 pinMode(data,OUTPUT);
 pinMode(clock_,OUTPUT);
 pinMode(latch,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(9,OUTPUT);
}


void loop() {

  
  digitalWrite(latch, LOW);
  shiftOut(data, clock_, MSBFIRST, 0b0101);
  digitalWrite(latch, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9, LOW);
  delay(1000);

  digitalWrite(latch, LOW);
  shiftOut(data, clock_, MSBFIRST, 0);
  digitalWrite(latch, HIGH);
  delay(1000);
  
  digitalWrite(latch, LOW);
  shiftOut(data, clock_, MSBFIRST, 0b1010);
  digitalWrite(latch, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9, HIGH);
  delay(1000);

  digitalWrite(latch, LOW);
  shiftOut(data, clock_, MSBFIRST, 0);
  digitalWrite(latch, HIGH);
  delay(1000);

}
