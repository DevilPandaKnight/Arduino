//sample rate is 76.8KHz in theory (prescale 16), but limited by the
//serial transimition rate (115200), so the matlab can only do
//sample rate 5867.
const unsigned char PS_2 = (1 << ADPS0);
const unsigned char PS_4 = (1 << ADPS1);
const unsigned char PS_8 = (1 << ADPS1) | (1 << ADPS0);
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void setup() {
 Serial.begin(230400);
 pinMode(A0,INPUT);
 ADCSRA &= ~PS_128;  // remove bits set by Arduino library
 ADCSRA |= PS_64;    // 16 prescaler for 76.9 KHz
}

int i;
void loop() {
  for (;;){
    unsigned short a = analogRead(A0);
    Serial.write((char*)&a,2);
  }
  /*  test frequency
  long t0, t;

  t0 = micros();
  for(int i=0; i<1000; i++) {
    analogRead(A0);
  }
  t = micros()-t0;  // calculate elapsed time

  Serial.print("Time per sample: ");
  Serial.println((float)t/1000);
  Serial.print("Frequency: ");
  Serial.println((float)1000*1000000/t);
  Serial.println();
  delay(2000);
  */
}
