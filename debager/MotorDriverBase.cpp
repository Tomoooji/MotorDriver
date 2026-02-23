#include "MotorDriverBase.h"

#define sign(x) (x>0) - (x<0) 

MotorDriverBase::MotorDriverBase(bool digital, const uint8_t MIN, const uint8_t MAX):
  _MODE(digital? MODE_DIGITAL: MODE_ANALOG), _MIN(MIN), _MAX(MAX){}

bool MotorDriverBase::attach(uint8_t pin1, uint8_t pin2){
  if(this->checkPin(pin1) * this->checkPin(pin2)){
    if(this->checkPin(pin1)+this->checkPin(pin2) == MODE_ANALOG*2){
      this->_MODE = MODE_ANALOG;
    }
    else{
      this->_MODE = MODE_DIGITAL;
    }
    return true;
  }
  else{
    this->_MODE = MODE_INVALID;
    return false;
  }
}

void MotorDriverBase::setAccel(float accel, float decel){
  this->_accel = accel; this->_decel = decel;
}

bool MotorDriverBase::setVelocity(int velocity){
  if(abs(velocity) <= LIMIT_MAX){
    this-> setSpeed(abs(velocity));
    this-> setDirec(velocity < 0);
    return true;
  }
  return false;
}
void MotorDriverBase::setSpeed(uint8_t speed){
  this-> _velocity = constrain(speed, this->_MIN, this->_MAX) * sign(this->_velocity);
}
void MotorDriverBase::setDirec(bool reverse){
  this->_velocity *= -reverse;
  //return true;
}

int MotorDriverBase::move(){
  return this->_velocity ? (this->_velocity > 0 ? this->moveForward() : this->moveBackward()) : this->stop();
}


int MotorDriverBase::accelLiner(uint8_t target){
  //if(target==-1)target=this->MAX_SPEED;
  if(target > this->speed() + this->accel()){ // 加速
    this-> setSpeed(this->speed() + this->accel());
  }
  else if(target < this->speed() - this->accel()){ // 減速
    this-> setSpeed(this->speed() - this->accel());
  }
  else{ // targetとの差がaccel以下の時はtargetを直代入
    this-> setVelocity(target);
  }
}

int MotorDriverBase::decelLiner(uint8_t target){
  //if(target==-1)target=this->MIN_SPEED;
  if(target < this->speed() - this->decel()){ // 減速
    this-> setSpeed(this->speed() - this->decel());
  }
  else if(target > this->speed() + this->decel()){ // 加速
    this-> setSpeed(this->speed() + this->decel());
  }
  else{ // targetとの差がdecel以下の時はtargetを直代入
    this-> setVelocity(target);
  }
}

