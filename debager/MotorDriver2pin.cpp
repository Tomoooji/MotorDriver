#if defined(ARDUINO_ARCH_AVR)
#include "MotorDriver2pin.h"

bool MotorDriver2pin::attach(uint8_t pin1, uint8_t pin2){
  MotorDriverBase::switchMode(pin1, pin2);
  switch(this->_MODE){
    case MODE_DIGITAL:
    case MODE_ANALOG:
      this->_pin1 = pin1;
      this->_pin2 = pin2;
      pinMode(this->_pin1, OUTPUT);
      pinMode(this->_pin2, OUTPUT);
      return true;
    case MODE_INVALID:
      return false;
  }
}


int MotorDriver2pin::moveForward(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pin1, HIGH);
      digitalWrite(this->_pin2, LOW);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pin1, this->speed());
      analogWrite(this->_pin2, 0);
      break;
    case MODE_INVALID:
      return 0;
  }
  return this->speed();
}

int MotorDriver2pin::moveBackward(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pin1, LOW);
      digitalWrite(this->_pin2, HIGH);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pin1, 0);
      analogWrite(this->_pin2, this->speed());
      break;
    case MODE_INVALID:
      return 0;
  }
  return this->speed();
}

int MotorDriver2pin::stop(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pin1, LOW);
      digitalWrite(this->_pin2, LOW);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pin1, 0);
      analogWrite(this->_pin2, 0);
      break;
    case MODE_INVALID:
      return 0;
  }
  return 0;
}

int MotorDriver2pin::lock(){
  switch(this->_MODE){
    case MODE_DIGITAL:
      digitalWrite(this->_pin1, HIGH);
      digitalWrite(this->_pin2, HIGH);
      break;
    case MODE_ANALOG:
      analogWrite(this->_pin1, this->speed());
      analogWrite(this->_pin2, this->speed());
      break;
    case MODE_INVALID:
      return 0;
  }
  return this->speed();
}


#endif