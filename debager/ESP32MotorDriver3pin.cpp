#if defined(ESP32)
#include "ESP32MotorDriver3pin.h"

bool ESP32MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2){
  return this->attach(pin1, pin2, this->_pinPWM);
}

bool ESP32MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  this->_pin1 = pin1;
  this->_pin2 = pin2;
  this->_pinPWM = pinPWM;
  pinMode(this->_pin1, OUTPUT);
  pinMode(this->_pin2, OUTPUT);
  ledcAttach(this->_pinPWM, 12800, 8);
  return true;
}
    // bool isAvailablePWM(uint8_t pin);
    // bool isInputOnly(uint8_t pin);

int ESP32MotorDriver3pin::moveForward(){
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, LOW);
  ledcWrite(this->_pinPWM, this->speed());
  return this->speed();
}

int ESP32MotorDriver3pin::moveBackward(){
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, HIGH);
  ledcWrite(this->_pinPWM, this->speed());
  return this->speed();
}

int ESP32MotorDriver3pin::stop(){
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, LOW);
  ledcWrite(this->_pinPWM, 0);
  return 0;
}

int ESP32MotorDriver3pin::lock(){
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, HIGH);
  ledcWrite(this->_pinPWM, this->speed());
  return this->speed();
}

#endif