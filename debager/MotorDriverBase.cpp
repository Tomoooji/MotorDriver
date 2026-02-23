#include "MotorDriverBase.h"

#define sign(x) (x>0) - (x<0) 


MotorDriverBase::MotorDriverBase(bool digital, const uint8_t MIN, const uint8_t MAX):
  _MODE(digital? MODE_DIGITAL: MODE_ANALOG), _MIN(MIN), _MAX(MAX), _velocity(0), _accel(0), _decel(0){}


void MotorDriverBase::switchMode(uint8_t pin1, uint8_t pin2){
  if(this->checkPin(pin1) * this->checkPin(pin2)){
    if(this->checkPin(pin1)+this->checkPin(pin2) == MODE_ANALOG*2){
      this->_MODE = MODE_ANALOG;
    }
    else{
      this->_MODE = MODE_DIGITAL;
    }
  }
  else{
    this->_MODE = MODE_INVALID;
  }
}

void MotorDriverBase::setAccel(float accel, float decel){
  this->_accel = accel; this->_decel = decel;
}

bool MotorDriverBase::setVelocity(int velocity){
  if(abs(velocity) <= LIMIT_MAX){
    this->setSpeed(abs(velocity));
    this->setDirec(velocity < 0);
    return true;
  }
  return false;
}
void MotorDriverBase::setSpeed(uint8_t speed){
  switch(this->_MODE){
    case MODE_DIGITAL:
      this->_velocity = speed > this->_MIN? this->_MAX: this->_MIN;
      return;
    case MODE_ANALOG:
      this->_velocity = constrain(speed, this->_MIN, this->_MAX) * sign(this->_velocity);
      return;
    case MODE_INVALID:
      return;
  }
}
void MotorDriverBase::setDirec(bool reverse){
  this->_velocity *= -reverse;
  //return true;
}

int MotorDriverBase::move(int velocity, bool usedefault){
  if(usedefault)this->_velocity = velocity;
  return this->_velocity? (this->_velocity > 0? this->moveForward(): this->moveBackward()): this->stop();
}


int MotorDriverBase::accelLiner(uint8_t target){
  if(this->_MODE != MODE_ANALOG) return 0;
  if(target > this->speed() + this->accel()){ // 加速
    this->setSpeed(this->speed() + this->accel());
  }
  else if(target < this->speed() - this->accel()){ // 減速
    this->setSpeed(this->speed() - this->accel());
  }
  else{ // targetとの差がaccel以下の時はtargetを直代入
    this->setVelocity(target);
  }
  return this->velocity();
}

int MotorDriverBase::decelLiner(uint8_t target){
  if(this->_MODE != MODE_ANALOG) return 0;
  if(target < this->speed() - this->decel()){ // 減速
    this->setSpeed(this->speed() - this->decel());
  }
  else if(target > this->speed() + this->decel()){ // 加速
    this->setSpeed(this->speed() + this->decel());
  }
  else{ // targetとの差がdecel以下の時はtargetを直代入
    this->setVelocity(target);
  }
  return this->velocity();
}

