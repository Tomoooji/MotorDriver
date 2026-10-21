#pragma once
#include "DigitalMotorDriver.h"

template <int MAX_SPEED_VALUE = 255, int PIN_COUNT = 2>
class AnalogMotor_Base : public MotorInterface {
protected:
  const uint8_t (&_pins)[PIN_COUNT];
  int _speed = 0;

public:
  static constexpr int MAX_SPEED = MAX_SPEED_VALUE;
  static constexpr int PIN_NUM = PIN_COUNT;
  AnalogMotor_Base(const uint8_t (&pins)[PIN_COUNT]) : _pins(pins) {}
  using MotorInterface::write;
  virtual int write (int speed) {
    this->setSpeed(speed);
    return this->write();
  }
  int setSpeed(int speed) {
    this->_speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
    return this->_speed;
  }
  const int getSpeed() const { return this->_speed; }
  const uint8_t getPin(uint8_t idx) const {
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

#if (ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0))
class AnalogMotor_ESP32 : public AnalogMotor_Base<255, 2> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
    ledcAttach(this->_pins[0], 12800, 8);
    ledcAttach(this->_pins[1], 12800, 8);
  }
  int write() override {
    ledcWrite(this->_pins[0], max(this->_speed, 0));
    ledcWrite(this->_pins[1], max(-this->_speed, 0));
    return this->_speed;
  }
};
#else
class AnalogMotor_ESP32 : public AnalogMotor_Base<255, 2> {
private:
  inline static uint8_t _instance_count = 0;
  inline static constexpr uint8_t _ledc_channel_all[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  const uint8_t _ledc_channel_1;
  const uint8_t _ledc_channel_2;

public:
  AnalogMotor_ESP32(const uint8_t (&pins)[2], const uint8_t ledc_channel_1, const uint8_t ledc_channel_2)
      : AnalogMotor_Base<255, 2>(pins), _ledc_channel_1(ledc_channel_1), _ledc_channel_2(ledc_channel_2) {_instance_count++; }
  AnalogMotor_ESP32(const uint8_t (&pins)[2], const uint8_t ledc_channel[2])
      : AnalogMotor_ESP32(pins, ledc_channel[0], ledc_channel[1]) {}
  AnalogMotor_ESP32(const uint8_t (&pins)[2])
      : AnalogMotor_ESP32(pins, _ledc_channel_all[_instance_count%8*2], _ledc_channel_all[_instance_count%8*2+1]) {}
  using AnalogMotor_Base::write;
  void begin() override {
    ledcSetup(this->_ledc_channel_1, 12800, 8);
    ledcSetup(this->_ledc_channel_2, 12800, 8);
    ledcAttachPin(this->_pins[0], this->_ledc_channel_1);
    ledcAttachPin(this->_pins[1], this->_ledc_channel_2);
  }
  int write() override {
    ledcWrite(this->_ledc_channel_1, max(this->_speed, 0));
    ledcWrite(this->_ledc_channel_2, max(-this->_speed, 0));
    return this->_speed;
  }
};
#endif
using AnalogMotor = AnalogMotor_ESP32;

#if (ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0))
class AnalogMotor_3pin_ESP32 : public AnalogMotor_Base<255, 3> {
public:
  using AnalogMotor_Base::AnalogMotor_Base;
  using AnalogMotor_Base::write;
  void begin() override {
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
#else
class AnalogMotor_3pin_ESP32 : public AnalogMotor_Base<255, 3> {
private:
  inline static uint8_t _instance_count = 0;
  inline static constexpr uint8_t _ledc_channel_all[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  const uint8_t _ledc_channel;
public:
  AnalogMotor_3pin_ESP32(const uint8_t (&pins)[3], const uint8_t ledc_channel)
      : AnalogMotor_Base<255, 3>(pins), _ledc_channel(ledc_channel) { _instance_count++; }
  AnalogMotor_3pin_ESP32(const uint8_t (&pins)[3])
      : AnalogMotor_3pin_ESP32(pins, _ledc_channel_all[_instance_count%8]) {}
  using AnalogMotor_Base::write;
  void begin() override {
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
    ledcSetup(this->_ledc_channel, 12800, 8);
    ledcAttachPin(this->_pins[2], this->_ledc_channel);
  }
  int write() override {
    digitalWrite(this->_pins[0], this->_speed > 0);
    digitalWrite(this->_pins[1], this->_speed < 0);
    ledcWrite(this->_ledc_channel, abs(this->_speed));
    return this->_speed;
  }
};
#endif
using AnalogMotor_3pin = AnalogMotor_3pin_ESP32;

#endif

#if __cplusplus >= 202002L
#include <concepts>
template <class MD>
concept AnalogMotorConcept = std::derived_from<MD, MotorInterface> && requires(MD m) {
  { m.getSpeed() } -> std::convertible_to<int>;
  { m.write(0) } -> std::convertible_to<int>;
};
#endif