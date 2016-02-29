#include "MicroMouse.h"
#define IN_1 3 
#define IN_2 2
#define IN_3 23
#define IN_4 22
#define LSENSOR 18
#define RSENSOR 17
#define enable_1 4
#define enable_2 21


MicroMouse mouse(IN_1,IN_2,IN_3,IN_4,enable_1,enable_2);

void setup() {
  mouse.setLeftSensor(LSENSOR);
  mouse.setRightSensor(RSENSOR);
  Serial.begin(9600);
}

void loop() {
  mouse.moveForward();
  Serial.println(mouse.readLeftSensor());
  Serial.println(mouse.readRightSensor());
  Serial.println("------------------------------------------------");
  delay(50);
}
