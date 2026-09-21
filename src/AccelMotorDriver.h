#pragma once
#include "AnalogMotorDriver.h"

template <AnalogMotorConcept MD>
class _AccelMotor : public MD {
private:
  const int& _accel;
  const int& _decel;
  int _target = 0;

public:
  _AccelMotor(const uint8_t (&pins)[MD::PIN_NUM], const int& accel, const int& decel)
      : MD(pins), _accel(accel), _decel(decel) {}
  _AccelMotor(const uint8_t (&pins)[MD::PIN_NUM], const int& accel)
      : _AccelMotor(pins, accel, accel) {}

  int write() override {
    int delta_speed = min(this->_target - this->_speed, 
                          (this->_speed > this->_target ? this->_accel : this->_decel));
    this->write(this->_speed + delta_speed);
    return this->_speed + delta_speed;
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
using AccelMotor = _AccelMotor<AnalogMotor_Arduino>;
using AccelMotor_3pin = _AccelMotor<AnalogMotor_3pin_Arduino>;

#elif defined(ESP32)
using AccelMotor = _AccelMotor<AnalogMotor_ESP32>;
using AccelMotor_3pin = _AccelMotor<AnalogMotor_3pin_ESP32>;

#endif