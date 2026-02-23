#ifndef MORTORDRIVER_3PIN_ESP32_H
#define MORTORDRIVER_3PIN_ESP32_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class ESP32MotorDriver3pin : public MotorDriverBase{
  public:
    using MotorDriverBase::MotorDriverBase;
    void attach(uint8_t pin1, uint8_t pin2) override;
    void attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM);
    void forward() override;
    void backward() override;
    void stop() override;
    void lock() override;
  private:
    uint8_t pinPWM = 15;
};
/*
class ESPL298N{
  public:
    ESPMotorDriver3pin A, B;
};
*/

#endif