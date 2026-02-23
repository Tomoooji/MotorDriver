#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
// ↑ #pragma onceでええらしい

#include <Arduino.h>

constexpr uint8_t SPEED_MAX = 255;
constexpr uint8_t SPEED_MIN = 0;

class MotorDriver{
  public:
    // コンストラクタとかいうらしい //
    //MotorDriver();
    // デストラクタとかいうらしい //
    //~MotorDriver(); 
    // 基本操作用 //
    void Attach(uint8_t pin1, uint8_t pin2);
      virtual void Attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM); // ここでは使わない
    void SetSpeed(int speed = SPEED_MAX);
    uint8_t GetSpeed();
    virtual void Forward();
    virtual void Backward();
    virtual void Stop(); // Nutral用(別にSetSpeed(0)→Forward()とかでもいい)
    virtual void Lock(); // 軸固定用
    // 加速度制御用 // decelは指定しない場合accelと同じにする
    void SetAccel(int accel);
    void SetAccel(int accel, int decel);
    uint8_t GetAccel();
    uint8_t GetDecel();
    // AccelLinerで減速、DecelLinerで加速するときはそれぞれaccelとdecelを使うことにする(一旦)
    void AccelLiner(int target = SPEED_MAX);
    void DecelLiner(int target = SPEED_MIN);

  protected:
    // Pins // 別に多分書かなくてもいいがデフォルトで10と11を使うことにしておく
    uint8_t pin1 = 10;
    uint8_t pin2 = 11;
    // Values //
    uint8_t speed = 0;
    uint8_t accel = 0;
    uint8_t decel = 0;
};

#endif