#include "MotorDriver3pin.h"

void MotorDriver3pin::Attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  this-> pinPWM = pinPWM;
  pinMode(this-> pin1,OUTPUT);
  pinMode(this-> pin2,OUTPUT);
  pinMode(this-> pinPWM,OUTPUT);
}

void MotorDriver3pin::Forward(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, LOW);
  analogWrite(this-> pinPWM, this-> speed);
}

void MotorDriver3pin::Backward(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, HIGH);
  analogWrite(this-> pinPWM, this-> speed);
}

void MotorDriver3pin::Stop(){
  digitalWrite(this-> pin1, LOW);
  digitalWrite(this-> pin2, LOW);
  analogWrite(this-> pinPWM, SPEED_MIN);
}

void MotorDriver3pin::Lock(){
  digitalWrite(this-> pin1, HIGH);
  digitalWrite(this-> pin2, HIGH);
  analogWrite(this-> pinPWM, this-> speed);
}


