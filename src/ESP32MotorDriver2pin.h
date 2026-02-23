#ifndef MORTORDRIVER_2PIN_ESP32_H
#define MORTORDRIVER_2PIN_ESP32_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class ESP32MotorDriver2pin : public MotorDriverBase{
  public:
    using MotorDriverBase::MotorDriverBase;
    void attach(uint8_t pin1, uint8_t pin2) override;
    void forward() override;
    void backward() override;
    void stop() override;
    void lock() override;
};

#endif