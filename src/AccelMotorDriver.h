#pragma once
#include "AnalogMotorDriver.h"

template<class MD>
class _AccelMotor : public MD {
private:
  int _accel, _decel;
  int _target = 0;
public:
  _AccelMotor(const int accel, const int decel) : _accel(accel), _decel(decel) {}
  _AccelMotor(const int accel) : _AccelMotor(accel, accel) {}

  int move_a() {
    int delta_speed = min(this->_target - this->_speed, (this->_speed > this->_target ? this->_accel : this->_decel));
    this->move(this->_speed + delta_speed);
    return this->_speed + delta_speed;
  }

  int move_a(int target) {
    this->set_target(target);
    return this->move_a();
  }

  int set_target(int target) {
    this->_target = constrain(target, -255, 255);
    return this->_target;
  }
  const int get_accel() {
    return this->_accel;
  }
  const int get_decel() {
    return this->_decel;
  }
};

#if defined(ARDUINO_ARCH_AVR)
using AccelMotor = _AccelMotor<AnalogMotor_Arduino>;
using AccelMotor_3pin = _AccelMotor<AnalogMotor_3pin_Arduino>;

#elif defined(ESP32)
using AccelMotor = _AccelMotor<AnalogMotor_ESP32>;
using AccelMotor_3pin = _AccelMotor<AnalogMotor_3pin_ESP32>;

#endif