#ifndef MOTORDRIVER_3PIN_H
#define MOTORDRIVER_3PIN_H

#include <Arduino.h>
#include "MotorDriver.h"

class MotorDriver3pin : public MotorDriver{
  public:
    void Attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM) override;
    //void SetSpeed(int speed);
    void Forward() override;
    void Backward() override;
    void Stop() override;
    void Lock() override;
  private:
    // Added Pins //
    uint8_t pinPWM;
};

class L298N{
  public:
    MotorDriver3pin A, B;
};

#endif