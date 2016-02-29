int leds[] = {5,6,7,8,9,10,11,12};
int onORoff[] = {0,0,0,0,0,0,0,0};
void setup() {
  Serial.begin(9600);
  for (int i = 5;i<=12;i++){
    pinMode(i,OUTPUT);
  }

}

int s;
#define num_1 lightLED('1');lightLED('6');
#define num_2 lightLED('1');lightLED('2');lightLED('5');lightLED('7');lightLED('8');
#define num_3 lightLED('2');lightLED('3');lightLED('5');lightLED('7');lightLED('8');
#define num_4 lightLED('6');lightLED('5');lightLED('8');lightLED('3');

void lightLED(int led){
  if (led <49 || led>56){return;}
  int val = s-49;
  if (onORoff[s-49] == 0){digitalWrite(leds[val],HIGH);onORoff[val] = 1;Serial.println("light on.");}
  else{digitalWrite(leds[val],LOW);onORoff[val] = 0;Serial.println("light off.");}
}

void loop() {
  s = Serial.read();
  lightLED(s);
}
