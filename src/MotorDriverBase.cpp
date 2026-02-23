#include "MotorDriverBase.h"

MotorDriverBase::MotorDriverBase(const int MaxSpeed, const int MinSpeed):
  MAX_SPEED(MaxSpeed), MIN_SPEED(MinSpeed){}

bool MotorDriverBase::setSpeed(int speed){
  if(speed <= this->MAX_SPEED && speed >= this->MIN_SPEED){
    this-> speed = speed;
    return true;
  }
  else{
    return false;
  }
}

uint8_t MotorDriverBase::getSpeed(){
  return this-> speed;
}

void MotorDriverBase::move(int direc){
  if(direc > 0){
    this-> forward();
  }
  else if(direc < 0){
    this-> backward();
  }
  else{
    this-> stop();
  }
}

void MotorDriverBase::setAccel(uint8_t accel){
  this-> setAccel(accel, accel);
}

void MotorDriverBase::setAccel(uint8_t accel, uint8_t decel){
  this-> accel = accel;
  this-> decel = decel;
}

uint8_t MotorDriverBase::getAccel(){
  return this-> accel;
}

uint8_t MotorDriverBase::getDecel(){
  return this-> decel;
}

void MotorDriverBase::accelLiner(int target){
  if(target==-1)target=this->MAX_SPEED;
  if(target > this-> speed + this-> accel){ // 加速
    this-> setSpeed(this-> speed + this-> accel);
  }
  else if(target < this-> speed - this-> accel){ // 減速
    this-> setSpeed(this-> speed - this-> accel);
  }
  else{ // targetとの差がaccel以下の時はtargetを直代入
    this-> setSpeed(target);
  }
}

void MotorDriverBase::decelLiner(int target){
  if(target==-1)target=this->MIN_SPEED;
  if(target < this-> speed - this-> decel){ // 減速
    this-> setSpeed(this-> speed - this-> decel);
  }
  else if(target > this-> speed + this-> decel){ // 加速
    this-> setSpeed(this-> speed + this-> decel);
  }
  else{ // targetとの差がdecel以下の時はtargetを直代入
    this-> setSpeed(target);
  }
}
