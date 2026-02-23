#if defined(ESP32)
#include "ESP32MotorDriver3pin.h"

void ESP32MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2){
  this-> attach(pin1, pin2, this->pinPWM);
}

void ESP32MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  this-> pinPWM = pinPWM;
  pinMode(this-> pin1, OUTPUT);
  pinMode(this-> pin2, OUTPUT);
  ledcAttach(this-> pinPWM, 12800, 8);
}

void ESP32MotorDriver3pin::forward(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, LOW);
  ledcWrite(this-> pinPWM, this-> speed);
}

void ESP32MotorDriver3pin::backward(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, HIGH);
  ledcWrite(this-> pinPWM, this-> speed);
}

void ESP32MotorDriver3pin::stop(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, LOW);
  ledcWrite(this-> pinPWM, 0);
}

void ESP32MotorDriver3pin::lock(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, HIGH);
  ledcWrite(this-> pinPWM, this-> speed);
}

#endif