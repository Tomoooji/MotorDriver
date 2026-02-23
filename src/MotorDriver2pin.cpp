#include "MotorDriver2pin.h"

void MotorDriver2pin::attach(uint8_t pin1, uint8_t pin2){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  pinMode(this-> pin1,OUTPUT);
  pinMode(this-> pin2,OUTPUT);
}

void MotorDriver2pin::forward(){
  analogWrite(this-> pin1, this-> speed);
  analogWrite(this-> pin2, 0);
}

void MotorDriver2pin::backward(){
  analogWrite(this-> pin1, 0);
  analogWrite(this-> pin2, this-> speed);
}

void MotorDriver2pin::stop(){
  analogWrite(this-> pin1, 0);
  analogWrite(this-> pin2, 0);
}

void MotorDriver2pin::lock(){
  analogWrite(this-> pin1, this-> speed);
  analogWrite(this-> pin2, this-> speed);
}

