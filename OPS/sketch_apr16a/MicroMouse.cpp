#include "MicroMouse.h"

MicroMouse::MicroMouse(uint8_t in1,uint8_t in2, uint8_t in3,uint8_t in4,uint8_t enable1, uint8_t enable2)
{
    // Configure the pins
    _motor_1.IN_1 = in1;
    _motor_1.IN_2 = in2;
    _motor_2.IN_1 = in3;
    _motor_2.IN_2 = in4;
    _motor_1.enable = enable1;
    _motor_2.enable = enable2;

    pinMode(_motor_1.IN_1, OUTPUT);
    pinMode(_motor_1.IN_2, OUTPUT);
    pinMode(_motor_2.IN_1, OUTPUT);
    pinMode(_motor_2.IN_2, OUTPUT);
    pinMode(_motor_1.enable, OUTPUT);
    pinMode(_motor_2.enable, OUTPUT);

    // Set the starting parameters
    _motor_1.speed = 0;
    _motor_2.speed = 0;
    _leftSensor = -1;
    _rightSensor = -1;

    // Set the control parameters
    _time = millis();
    _integral = 0;
    _kp = 0.04;
    _ki = 0.04;
    _rightBaseline = 800;
    _leftBaseline = 960;
    _tolerance = 100;
}


void MicroMouse::wheelForward(Motor& motor){
  motor.setWheelDirection(_forward); 
}

void MicroMouse::wheelBackward(Motor& motor){
  motor.setWheelDirection(_backward);
}

void MicroMouse::change_speed(unsigned spd){
    if(spd > MAXSPEED || spd < 0){
        return;
    }
    _motor_1.setSpeed(spd);
    _motor_2.setSpeed(spd);
}

void MicroMouse::change_motor_speed(Motor& motor, unsigned spd){
    if(spd > MAXSPEED || spd < 0 || motor.enable == -1){
        return;
    }
    motor.setSpeed(spd);
}

void MicroMouse::stopMotor(){
    change_speed(0);
}


void MicroMouse::setLeftSensor(uint8_t pin){
    pinMode(pin, INPUT);
    _leftSensor = pin;
}

void MicroMouse::setRightSensor(uint8_t pin){
    pinMode(pin, INPUT);
    _rightSensor = pin;
}

int MicroMouse::readLeftSensor() const{
    if(_leftSensor == -1)return 0;
    return acquireSensor(_leftSensor);
}

int MicroMouse::readRightSensor() const{
    if(_rightSensor == -1)return 0;
    return acquireSensor(_rightSensor);
}


void MicroMouse::moveForward(){
    // This is where our controller will be implemented since we only
  	// need it when going forward.

  	// Find your position relative to the left and right walls
  	_rightDistance = readRightSensor();
  	_leftDistance = readLeftSensor();

  	// Compute the error in these measurements
    _rightError = _rightBaseline - _rightDistance;
    _leftError = _leftBaseline - _leftDistance;
          
         _time = millis()-_time;
  	// Compute the total error and integral error
  	_totalError = _rightError - _leftError;
  	_integral += _totalError*_time*1e-3;

  	// Decide how to correct based on the error
        _rightSpeed = _motor_1.speed;
        _leftSpeed = _motor_2.speed;
  	if(_totalError < -_tolerance){
 	_rightSpeed += abs(_kp*_totalError + _ki*_integral); //shift left
 	change_motor_speed(_motor_1,_rightSpeed);
        _leftSpeed -= abs(_kp*_totalError + _ki*_integral);
        change_motor_speed(_motor_2,_leftSpeed);
  	}
  	else if (_totalError > _tolerance){
        _rightSpeed -= abs(_kp*_totalError + _ki*_integral);	//shift right
        change_motor_speed(_motor_1, _rightSpeed);
        _leftSpeed += abs(_kp*_totalError + _ki*_integral);
        change_motor_speed(_motor_2,_leftSpeed);
  	}
  	else{
        motor_direction(_forward);
        change_speed(MAXSPEED);
  	}
     Serial.print("left error: ");
     Serial.println(_leftError);
     Serial.print("right error: ");
     Serial.println(_rightError);
     Serial.print("left speed: ");
     Serial.println(_leftSpeed);
     Serial.print("right speed: ");
     Serial.println(_rightSpeed);
     Serial.print("integral: ");
     Serial.println(_integral);
     _time = millis();
}

void MicroMouse::moveBackward(){
    motor_direction(_backward);
    change_speed(MAXSPEED);
}

void MicroMouse::turnLeft(){
    motor_direction(_left);
    change_speed(MAXSPEED);
    delay(1500);
    motor_direction(_forward);
}

void MicroMouse::turnRight(){
    motor_direction(_right);
    change_speed(MAXSPEED);
    delay(1500);
    motor_direction(_forward);
}

int MicroMouse::acquireSensor(int pin) const{
    int sum = 0;
    for(int i = 0;i<NUMBER_OF_SAMPLE;i++){
        sum += analogRead(pin);
    }
    return sum/NUMBER_OF_SAMPLE;
}

void MicroMouse::motor_direction(int d){
  switch (d) {
    case _forward:
      wheelForward(_motor_1);
      wheelForward(_motor_2);
      break;
    case _backward:
      wheelBackward(_motor_1);
      wheelBackward(_motor_2);
      break;
    case _left:
      wheelForward(_motor_1);
      wheelBackward(_motor_2);
      break;
    case _right:
      wheelBackward(_motor_2);
      wheelForward(_motor_1);
      break;
    default:
    break;
  }
}
