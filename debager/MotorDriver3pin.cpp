#include "MotorDriver3pin.h"

bool MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2){
  return this-> attach(pin1, pin2, this->_pinPWM);
}

bool MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  MotorDriverBase::attach(pin1, pin2);
  if(isInputOnly(pinPWM) || this->_MODE == INVALID){
    return false;
  }else{
    this->_pin1 = pin1;
    this->_pin2 = pin2;
    this->_pinPWM = pinPWM;
    pinMode(this->_pin1, OUTPUT);
    pinMode(this->_pin2, OUTPUT);
    pinMode(this->_pinPWM, OUTPUT);
    this->_MODE = (isDigitalOnly(pinPWM) || this->_MODE == DIGITAL)? DIGITAL: ANALOG;
    return true;
  }
}

int MotorDriver3pin::moveForward(){
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, LOW);
  analogWrite(this-> _pinPWM, this->speed());
  return this->speed();
}

int MotorDriver3pin::moveBackward(){
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, HIGH);
  analogWrite(this-> _pinPWM, this->speed());
  return this->speed();
}

int MotorDriver3pin::stop(){
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, LOW);
  analogWrite(this-> _pinPWM, 0);
  return 0;
}

int MotorDriver3pin::lock(){
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, HIGH);
  analogWrite(this-> _pinPWM, this->speed());
  return this->speed();
}

