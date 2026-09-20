#pragma once
#include <Arduino.h>

class DigitalMotor {
private:
  const uint8_t (&_pins)[2];
  int _direction = 0;

public:
  DigitalMotor(const uint8_t (&pins)[2]) : _pins(pins) {}
  void begin() {
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
  }
  void move(int direction) {
    this->_direction = constrain(direction, -1, 1);
    digitalWrite(this->_pins[0], this->_direction > 0);
    digitalWrite(this->_pins[1], this->_direction < 0);
  }
  const uint8_t getPin(const uint8_t idx) {
    return idx < 2 ? this->_pins[idx] : 0;
  }
  const int getDirection() { return this->_direction; }
};
