#pragma once
#include <Arduino.h>

template <int MAX_SPEED = 255, int PIN_NUM = 2> class AnalogMotor_Base {
protected:
  const uint8_t (&_pins)[PIN_NUM];
  int _speed = 0;

public:
  AnalogMotor_Base(const uint8_t (&pins)[PIN_NUM]) : _pins(pins) {}
  virtual void begin();
  virtual int write() = 0;
  int write(int speed) {
    this->setSpeed(speed);
    return this->write();
  }
  int setSpeed(int speed) {
    this->_speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    return this->_speed;
  }
  const int getSpeed() { return this->_speed; }
  const uint8_t getPin(uint8_t idx) {
    return idx < PIN_NUM ? this->_pins[idx] : 0;
  }
};

#if defined(ARDUINO_ARCH_AVR)

class AnalogMotor_Arduino : public AnalogMotor_Base<255, 2> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
  }
  int write() override {
    analogWrite(this->_pins[0], max(this->_speed, 0));
    analogWrite(this->_pins[1], max(-this->_speed, 0));
    return this->_speed;
  }
};
using AnalogMotor = AnalogMotor_Arduino;

class AnalogMotor_3pin_Arduino : public AnalogMotor_Base<255, 3> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
    this->_pins = pins;
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
    pinMode(this->_pins[2], OUTPUT);
  }
  int write() override {
    digitalWrite(this->_pins[0], this->_speed > 0);
    digitalWrite(this->_pins[1], this->_speed < 0);
    analogWrite(this->_pins[2], abs(this->_speed));
    return this->_speed;
  }
};
using AnalogMotor_3pin = AnalogMotor_3pin_Arduino;

#elif defined(ESP32)

class AnalogMotor_ESP32 : public AnalogMotor_Base<255, 2> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
    this->_pins = pins;
    ledcAttach(this->_pins[0], 12800, 8);
    ledcAttach(this->_pins[1], 12800, 8);
  }
  int write() override {
    ledcWrite(this->_pins[0], max(this->_speed, 0));
    ledcWrite(this->_pins[1], max(-this->_speed, 0));
    return this->_speed;
  }
};
using AnalogMotor = AnalogMotor_ESP32;

class AnalogMotor_3pin_ESP32 : public AnalogMotor_Base<255, 3> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
    this->_pins = pins;
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
    ledcAttach(this->_pins[2], 12800, 8);
  }
  int write() override {
    digitalWrite(this->_pins[0], this->_speed > 0);
    digitalWrite(this->_pins[1], this->_speed < 0);
    ledcWrite(this->_pins[2], abs(this->_speed));
    return this->_speed;
  }
};
using AnalogMotor_3pin = AnalogMotor_3pin_ESP32;

#endif

/*
#include "PCA9685.h"

class PCAMotor : public AnalogMotor_Base<255, 2> {
private:
  PCA9685 &_pwm;

public:
  PCAMotor(PCA9685 &pwm, const uint8_t pins[2])
      : _pwm(pwm), AnalogMotor_Base<255, 2>(pins) {}
  using AnalogMotor_Base::write;
  void begin() override {}
  int write() override {
    this->_pwm.setPWM(this->_pins[0], 0, max(this->_speed, 0) * 16);
    this->_pwm.setPWM(this->_pins[1], 0, max(-this->_speed, 0) * 16);
    return this->_speed;
  }
};
//*/