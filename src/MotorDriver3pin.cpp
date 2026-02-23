#include "MotorDriver3pin.h"

void MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2){
  this-> attach(pin1, pin2, this->pinPWM);
}

void MotorDriver3pin::attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  this-> pinPWM = pinPWM;
  pinMode(this-> pin1,OUTPUT);
  pinMode(this-> pin2,OUTPUT);
  pinMode(this-> pinPWM,OUTPUT);
}

void MotorDriver3pin::forward(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, LOW);
  analogWrite(this-> pinPWM, this-> speed);
}

void MotorDriver3pin::backward(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, HIGH);
  analogWrite(this-> pinPWM, this-> speed);
}

void MotorDriver3pin::stop(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, LOW);
  analogWrite(this-> pinPWM, 0);
}

void MotorDriver3pin::lock(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, HIGH);
  analogWrite(this-> pinPWM, this-> speed);
}

