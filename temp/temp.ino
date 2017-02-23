//sample rate is 76.8KHz in theory (prescale 16), but limited by the
//serial transimition rate (115200), so the matlab can only do
//sample rate 5867.
#include "/Users/jin/OneDrive/C++/Arduino/utility/fastSwitch.h"
#include "SoftArduino.hpp"
const unsigned char PS_2 = (1 << ADPS0);
const unsigned char PS_4 = (1 << ADPS1);
const unsigned char PS_8 = (1 << ADPS1) | (1 << ADPS0);
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

SoftArduino s;
void setup() {
 Serial.begin(230400);
}

void loop() {
  String str;
  if (Serial.available()){
    str = Serial.readStringUntil('\n');
    s.readCommand(str);
  }
 s.printPinInfo();
 delay(500);
}
