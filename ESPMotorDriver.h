#ifndef ESP_MOTORDRIVER_H
#define ESP_MOTORDRIVER_H

#include "MotorDriver.h"


class ESPMotorDriver : public MotorDriver{
  public:
    void Attach() override;
    void Forward() override;
    void Backward() override;
    void Stop() override;
    void Lock() override;

};

#endif