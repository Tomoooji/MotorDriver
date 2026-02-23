#if defined(ESP32)
#include "ESP32MotorDriver2pin.h"

bool ESP32MotorDriver2pin::attach(uint8_t pin1, uint8_t pin2){
  MotorDriverBase::attach(pin1, pin2);
  switch(this->_MODE){
    case MODE_DIGITAL:
      this->_pin1 = pin1;
      this->_pin2 = pin2;
      pinMode(this->_pin1, OUTPUT);
      pinMode(this->_pin2, OUTPUT);
      return true;
    case MODE_ANALOG:
      this->_pin1 = pin1;
      this->_pin2 = pin2;
      ledcAttach(this->_pin1, 12800, 8);
      ledcAttach(this->_pin2, 12800, 8);
      return true;
    case MODE_INVALID:
      return false;
  }
}

int ESP32MotorDriver2pin::moveForward(){
  ledcWrite(this->_pin1, this->speed());
  ledcWrite(this->_pin2, 0);
  return this->speed();
}

int ESP32MotorDriver2pin::moveBackward(){
  ledcWrite(this->_pin1, 0);
  ledcWrite(this->_pin2, this->speed());
  return this->speed();
}

int ESP32MotorDriver2pin::stop(){
  ledcWrite(this->_pin1, 0);
  ledcWrite(this->_pin2, 0);
  return 0;
}

int ESP32MotorDriver2pin::lock(){
  ledcWrite(this->_pin1, this->speed());
  ledcWrite(this->_pin2, this->speed());
  return this->speed();
}

#endif