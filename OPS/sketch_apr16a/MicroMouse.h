#ifndef MICROMOUSE_H
#define MICROMOUSE_H
#include <stdint.h>
#include <Arduino.h>
#include <math.h>
enum Direction{_forward,_left, _right,_backward};
#define MAXSPEED 80
#define NUMBER_OF_SAMPLE 80

struct Motor{
  unsigned speed;
  uint8_t IN_1;
  uint8_t IN_2;
  int8_t enable;
  void setSpeed(int spd){if(spd < 0){spd = -spd;}speed = spd;analogWrite(enable,spd);}
  Direction wheelDirection(){if(digitalRead(IN_1) == HIGH && digitalRead(IN_2) == LOW){return _forward;}return _backward;};
  void setWheelDirection(Direction dirc){
  if(_forward){
    digitalWrite(IN_1,HIGH); 
    digitalWrite(IN_2,LOW);
  }
  else if(_backward){
    digitalWrite(IN_1,LOW); 
    digitalWrite(IN_2,HIGH);
  }
}
  
};

class MicroMouse
{
    public:
        MicroMouse(uint8_t in1,uint8_t in2, uint8_t in3,uint8_t in4,uint8_t enable1, uint8_t enable2);
        void motor_direction(int d);
        void change_speed(unsigned spd);
        void stopMotor();


        void wheelForward(Motor& motor);
        void wheelBackward(Motor& motor);        
        
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();

        int readLeftSensor() const;
        void setLeftSensor(uint8_t pin);

        int readRightSensor() const;
        void setRightSensor(uint8_t pin);

        int acquireSensor(int pin) const;

    private:

        Motor _motor_1;
        Motor _motor_2;

        int8_t _leftSensor;
        int8_t _rightSensor;

        int _rightDistance;
        int _leftDistance;

        int _rightBaseline;
        int _leftBaseline;

        int _rightError;
        int _leftError;
        int _prevRightError;
        int _prevLeftError;
        int _totalError;
        int _tolerance;

        float _time;	// Time between control loop iterations
        int _integral;
        double _kp;	// Proportional gain
        double _ki;	// Integral gain

        int _leftSpeed;
        int _rightSpeed;
        int _delay_count = 0;


        void change_motor_speed(Motor& motor,unsigned speed);
};

#endif // MICROMOUSE_H
