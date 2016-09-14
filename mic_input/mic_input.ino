#include <SoftwareSerial.h>
//SoftwareSerial BT(9, 10); // RX, TX
#define LENGTH 8000
const int n = 20;
int record[LENGTH];
int out[2*n+1];
void setup() {
  pinMode(15, INPUT);
  analogWriteResolution(16);
//Serial.begin(9600);
}


unsigned counter = 0;

void loop() {

    int val = analogRead(15)*50;
    int temp = val + record[counter % LENGTH];
    record[counter % LENGTH] = val;
    
    out[n+n] = temp;
    int adder = 0;
    for (int i = -n;i<n;i++){
      adder += out[n+i];
    }
    temp = adder/(n+n);
    for(int i = -n;i<n;i++){
      out[n+i] = out[n+i+1];
    }
    
  analogWrite(A14,temp);
  counter++;
}
