#pragma once
#include "AnalogMotorDriver.h"

#if __cplusplus >= 202002L
template <AnalogMotorConcept MD>
#else
template <class MD>
#endif
class LowPassMotorWrapper : public MD {
private:
  const float _gain;
  int _target = 0;

public:
  LowPassMotorWrapper(const uint8_t (&pins)[MD::PIN_NUM], const float gain)
      : MD(pins), _gain(gain) {}

  int write() override {
    this->setSpeed(this->getSpeed() + (this->_target - this->getSpeed()) * this->_gain);
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
  const float getGain() { return this->_gain; }
};

#if defined(ARDUINO_ARCH_AVR)
using LowPassMotor = LowPassMotorWrapper<AnalogMotor_Arduino>;
using LowPassMotor_3pin = LowPassMotorWrapper<AnalogMotor_3pin_Arduino>;

#elif defined(ESP32)
using LowPassMotor = LowPassMotorWrapper<AnalogMotor_ESP32>;
using LowPassMotor_3pin = LowPassMotorWrapper<AnalogMotor_3pin_ESP32>;

#endif