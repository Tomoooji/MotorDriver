#ifndef MORTORDRIVER_3PIN_ESP32_H
#define MORTORDRIVER_3PIN_ESP32_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class ESP32MotorDriver3pin : public MotorDriverBase{
  private:
    uint8_t _pinPWM = DEFAULTPWMPIN;
  public:
    using MotorDriverBase::MotorDriverBase;
    bool attach(uint8_t pin1, uint8_t pin2) override;
    bool attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM);
    int moveForward() override;
    int moveBackward() override;
    int stop() override;
    int lock() override;
};
/*
class ESPL298N{
  public:
    ESPMotorDriver3pin A, B;
};
*/

#endif