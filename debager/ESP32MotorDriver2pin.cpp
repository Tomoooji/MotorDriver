#if defined(ESP32)
#include "ESP32MotorDriver2pin.h"

bool ESP32MotorDriver2pin::attach(uint8_t pin1, uint8_t pin2){
  this->_pin1 = pin1;
  this->_pin2 = pin2;
  ledcAttach(this->_pin1, 12800, 8);
  ledcAttach(this->_pin2, 12800, 8);
  return true;
}
    // bool isAvailablePWM(uint8_t pin);
    // bool isInputOnly(uint8_t pin);

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