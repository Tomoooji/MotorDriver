#pragma once
#include "AnalogMotorDriver.h"

template <AnalogMotorConcept MD>
class AccelMotorWrapper : public MD {
private:
  uint8_t _accel;
  uint8_t _decel;
  int _target = 0;

public:
  AccelMotorWrapper(std::array<uint8_t, MD::PIN_NUM> pins,uint8_t accel, uint8_t decel)
      : MD(pins), _accel(accel), _decel(decel) {}
  AccelMotorWrapper(std::array<uint8_t, MD::PIN_NUM> pins, uint8_t accel)
      : AccelMotorWrapper(pins, accel, accel) {}

  int write() override {
    int delta_speed = min(this->_target - this->getSpeed(), 
                          (this->getSpeed() > this->_target ? this->_accel : this->_decel));
    this->write(this->getSpeed() + delta_speed);
    return this->getSpeed();
  }

  int write(int target) override {
    this->setTarget(target);
    return this->write();
  }

  int writeDirect(int speed) {
    return MD::write(speed);
  }

  int writeDirect() {
    return MD::write();
  }

  int setTarget(int target) {
    this->_target = constrain(target, -MD::MAX_SPEED, MD::MAX_SPEED);
    return this->_target;
  }
  const int getAccel() { return this->_accel; }
  const int getDecel() { return this->_decel; }
};

#if defined(ARDUINO_ARCH_AVR)
using AccelMotor = AccelMotorWrapper<AnalogMotor_Arduino>;
using AccelMotor_3pin = AccelMotorWrapper<AnalogMotor_3pin_Arduino>;

#elif defined(ESP32)
using AccelMotor = AccelMotorWrapper<AnalogMotor_ESP32>;
using AccelMotor_3pin = AccelMotorWrapper<AnalogMotor_3pin_ESP32>;

#endif