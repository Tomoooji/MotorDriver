#ifndef MORTORDRIVER_2PIN_H
#define MORTORDRIVER_2PIN_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class MotorDriver2pin : public MotorDriverBase{
  public:
    using MotorDriverBase::MotorDriverBase;
    bool attach(uint8_t pin1, uint8_t pin2) override;
    int moveForward() override;
    int moveBackward() override;
    int stop() override;
    int lock() override;
};

#endif