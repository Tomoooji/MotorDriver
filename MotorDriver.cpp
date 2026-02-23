#include "MotorDriver.h"

//MotorDriver::MotorDriver(){}

//MotorDriver::~MotorDriver(){}

void MotorDriver::Attach(uint8_t pin1, uint8_t pin2){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  pinMode(this-> pin1,OUTPUT);
  pinMode(this-> pin2,OUTPUT);
}

void MotorDriver::Attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){}

void MotorDriver::SetSpeed(int speed){
  this-> speed = speed;
}

uint8_t MotorDriver::GetSpeed(){
  return this-> speed;
}

void MotorDriver::Forward(){
  analogWrite(this-> pin1, this-> speed);
  analogWrite(this-> pin2, 0);
}

void MotorDriver::Backward(){
  analogWrite(this-> pin1, 0);
  analogWrite(this-> pin2, this-> speed);
}

void MotorDriver::Stop(){
  analogWrite(this-> pin1, SPEED_MIN);
  analogWrite(this-> pin2, SPEED_MIN);
}

void MotorDriver::Lock(){
  analogWrite(this-> pin1, this-> speed);
  analogWrite(this-> pin2, this-> speed);
}

void MotorDriver::SetAccel(int accel){
  this-> SetAccel(accel, accel);
}

void MotorDriver::SetAccel(int accel, int decel){
  this-> accel = accel;
  this-> decel = decel;
}

uint8_t MotorDriver::GetAccel(){
  return this-> accel;
}

uint8_t MotorDriver::GetDecel(){
  return this-> decel;
}

void MotorDriver::AccelLiner(int target){
  if(target > this-> speed + this-> accel){ // 加速
    this-> speed += this-> accel;
  }
  else if(target < this-> speed - this-> accel){ // 減速
    this-> speed -= this-> accel;
  }
  else{ // targetとの差がaccel以下の時はtargetを直代入
    this-> speed = target;
  }
}

void MotorDriver::DecelLiner(int target){
  if(target < this-> speed - this-> decel){ // 減速
    this-> speed -= this-> decel;
  }
  else if(target > this-> speed + this-> decel){ // 加速
    this-> speed += this-> decel;
  }
  else{ // targetとの差がdecel以下の時はtargetを直代入
    this-> speed = target;
  }
}

