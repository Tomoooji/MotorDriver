#if defined(ARDUINO_ARCH_AVR)
#include "MotorDriver3pin.h"

bool MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2){
  return this->attach(pin1, pin2, this->_pinPWM);
}

bool MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  MotorDriverBase::switchMode(pin1, pin2);
  if(isInputOnly(pinPWM) || this->_MODE == MODE_INVALID){
    return false;
  }else{
    this->_pin1 = pin1;
    this->_pin2 = pin2;
    this->_pinPWM = pinPWM;
    pinMode(this->_pin1, OUTPUT);
    pinMode(this->_pin2, OUTPUT);
    pinMode(this->_pinPWM, OUTPUT);
    this->_MODE = (isDigitalOnly(pinPWM) || this->_MODE == MODE_DIGITAL)? MODE_DIGITAL: MODE_ANALOG;
    return true;
  }
}

int MotorDriver3pin::moveForward(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pinPWM, HIGH);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pinPWM, this->speed());
      break;
    case MODE_INVALID:
      return 0;
  }
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, LOW);
  return this->speed();
}

int MotorDriver3pin::moveBackward(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pinPWM, HIGH);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pinPWM, this->speed());
      break;
    case MODE_INVALID:
      return 0;
  }
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, HIGH);
  return this->speed();
}

int MotorDriver3pin::stop(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pinPWM, LOW);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pinPWM, 0);
      break;
    case MODE_INVALID:
      return 0;
  }
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, LOW);
  return this->speed();
}

int MotorDriver3pin::lock(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pinPWM, HIGH);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pinPWM, this->speed());
      break;
    case MODE_INVALID:
      return 0;
  }
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, HIGH);
  return this->speed();
}


#endif