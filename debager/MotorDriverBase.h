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
     Mode checkPin(uint8_t pin) const {return isInputOnly(pin)? MODE_INVALID: (isDigitalOnly(pin)? MODE_DIGITAL: MODE_ANALOG);}
    void switchMode_impl(uint8_t pin1, uint8_t pin2);
    
  private:
    int move_impl(int velocity, bool usedefault);

  public:
    // Constructors //
     MotorDriverBase(const bool digital, const uint8_t MIN, const uint8_t MAX);
    // MIN/MAX片方のみとdigitalだけ指定は不可
    MotorDriverBase(const bool digital = false): MotorDriverBase(digital, LIMIT_MIN, LIMIT_MAX){};
     // 全省略だとこっちが呼ばれる
    MotorDriverBase(const uint8_t MIN, const uint8_t MAX): MotorDriverBase(false, MIN, MAX){};
     // MIN&MAX指定(これでdigital指定するやつおらんやろ(その場合は一番上))
    virtual ~MotorDriverBase() = default;
    
    virtual bool attach(uint8_t pin1, uint8_t pin2) = 0; // returns ware pins correct
    // Setters //
    void setAccel(float accel, float decel);
     void setAccel(float accel){return this->setAccel(accel, accel);}
    bool setVelocity(int velocity); // velocity means +/-speed // returns was input corrected 
      void setSpeed(uint8_t speed); // change output value
      void setDirec(bool reverse = true); // makes direction reversed
    // Functions //
    int move(){return this->move_impl(0, true);}
    int move(int velocity){return this->move_impl(velocity,false);}
      virtual int moveForward() = 0;  // returns output speed
      virtual int moveBackward() = 0; // returns output speed
      virtual int stop() = 0; // may not have to be int ?
    virtual int lock() = 0; // also returns outputvalue (=stregth)
    int accelLinear(uint8_t target); // incliment speed until target speed, not velocity
     int accelLinear(){return this->accelLinear(this->_MAX);}
    int decelLinear(uint8_t target); // declement speed until target speed, not velocity
     int decelLinear(){return this->decelLinear(this->_MIN);}
    // Getters //
    uint8_t MIN() const {return this->_MIN;}
    uint8_t MAX() const {return this->_MAX;}
    int velocity() const {return this->_velocity;}
     uint8_t speed() const {return abs(this->_velocity);}
     bool direc() const {return (this->_velocity >= 0);}
    float accel() const {return this->_accel;}
    float decel() const {return this->_decel;}
};

#endif