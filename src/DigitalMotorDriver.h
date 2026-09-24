#pragma once
#include <Arduino.h>

class MotorInterface {
public:
  virtual ~MotorInterface() = default;
  virtual void begin() = 0;
  virtual int write() = 0;
};

class DigitalMotor : public MotorInterface {
private:
  const uint8_t (&_pins)[2];
  int _direction = 0;

public:
  DigitalMotor(const uint8_t (&pins)[2]) : _pins(pins) {}
  void begin() override {
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
  }
  int write(int direction) {
    this->setDirection(direction);
    return this->write();
  }
  int write() override {
    digitalWrite(this->_pins[0], this->_direction > 0);
    digitalWrite(this->_pins[1], this->_direction < 0);
    return this->_direction;
  }
  void setDirection(int direction) {
    this->_direction = constrain(direction, -1, 1);
  }
  const uint8_t getPin(const uint8_t idx) const {
    return idx < 2 ? this->_pins[idx] : 0;
  }
  const int getDirection() const { return this->_direction; }
};
