// Base class for controling motor driver by Arduino UNO and ESP32 //
#ifndef MOTORDRIVER_BASE_H
#define MOTORDRIVER_BASE_H
#include <Arduino.h>

class MotorDriverBase{
  public:
    MotorDriverBase(const int MaxSpeed = 255, const int MinSpeed = 0);
    const int MAX_SPEED;
    const int MIN_SPEED;
    //  //
    virtual void attach(uint8_t pin1, uint8_t pin2) = 0;
    void move(int direc = 1);
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void stop() = 0;
    virtual void lock() = 0;
    //  //
    virtual bool setSpeed(int speed);
      uint8_t getSpeed();
    void setAccel(uint8_t accel);
    void setAccel(uint8_t accel, uint8_t decel);
      uint8_t getAccel();
      uint8_t getDecel();
    void accelLiner(int target = -1);
    void decelLiner(int target = -1);
  protected:
    uint8_t pin1;
    uint8_t pin2;
    int speed;
  private:
    uint8_t accel = 0;
    uint8_t decel = 0;
};

#endif