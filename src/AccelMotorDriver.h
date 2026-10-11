#pragma once
#include "AnalogMotorDriver.h"

#if __cplusplus >= 202002L
template <AnalogMotorConcept MD>
#else
template <class MD>
#endif
class AccelMotorWrapper : public MD {
private:
  const uint8_t _accel;
  const uint8_t _decel;
  int _target = 0;

public:
  AccelMotorWrapper(const uint8_t (&pins)[MD::PIN_NUM], const uint8_t accel, const uint8_t decel)
      : MD(pins), _accel(accel), _decel(decel) {}
  AccelMotorWrapper(const uint8_t (&pins)[MD::PIN_NUM], const uint8_t accel_decel)
      : AccelMotorWrapper(pins, accel_decel, accel_decel) {}

  int write() override {
    int delta = this->_target - this->getSpeed();
    this->setSpeed(delta > this->_accel ? this->getSpeed() + this->_accel :
             (delta < -this->_decel ? this->getSpeed() - this->_decel :
              this->getSpeed() + delta));
    return MD::write();
  }

  int write(int target) override {
    this->setTarget(target);
    return this->write();
  }

  int writeDirect(int speed) {
    this->setSpeed(speed);
    return MD::write();
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