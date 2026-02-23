#ifndef MOTORDRIVER_BASE_H
#define MOTORDRIVER_BASE_H
#include <Arduino.h>
#include "MotorDriverConfig.h"

constexpr uint8_t LIMIT_MIN = 0;
constexpr uint8_t LIMIT_MAX = 255;

class MotorDriverBase{
  protected:
    uint8_t _pin1, _pin2;
    const uint8_t _MIN;
    const uint8_t _MAX;
    int _velocity;
    float _accel;
    float _decel;
    enum Mode{MODE_INVALID,MODE_DIGITAL,MODE_ANALOG} _MODE;
     Mode checkPin(uint8_t pin){return isInputOnly(pin)? MODE_INVALID: (isDigitalOnly(pin)? MODE_DIGITAL: MODE_ANALOG);}
  public:
    MotorDriverBase(const bool digital = false, const uint8_t MIN = LIMIT_MIN, const uint8_t MAX = LIMIT_MAX);
    virtual bool attach(uint8_t pin1, uint8_t pin2); // returns ware pins correct

    void setAccel(float accel, float decel);
     void setAccel(float accel){return this->setAccel(accel, accel);}
    bool setVelocity(int velocity); // velocity means +/-speed // returns was input corrected 
      void setSpeed(uint8_t speed); // change output value
      void setDirec(bool reverse = true); // makes direction reversed
 
    int move(int velocity, bool usedefault = false);
     int move(){this->move(0, true);}
      virtual int moveForward() = 0;  // returns output speed
      virtual int moveBackward() = 0; // returns output speed
      virtual int stop() = 0; // may not have to be int ?
    virtual int lock() = 0; // also returns outputvalue (=stregth)
    int accelLiner(uint8_t target); // incliment speed until target speed, not velocity
     int accelLiner(){return this->accelLiner(this->_MAX);}
    int decelLiner(uint8_t target); // declement speed until target speed, not velocity
     int decelLiner(){return this->decelLiner(this->_MIN);}

    uint8_t MIN(){return this->_MIN;}
    uint8_t MAX(){return this->_MAX;}
    int velocity(){return this->_velocity;}
     uint8_t speed(){return abs(this->_velocity);}
     bool reversed(){return (this->_velocity >= 0);}
    float accel(){return this->_accel;}
    float decel(){return this->_decel;}
  private:
};

#endif