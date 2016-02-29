#include <Stepper.h>
#define STEPS 100

Stepper stepper(STEPS,8,9,10,11);
int previous = 0;
void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(0);
  delay(200);
  if(abs(analogRead(0)-val) >= 5)
  stepper.step(val - previous);
  previous = val;
}


