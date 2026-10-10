// 基本的な使用方法 //

#include "DigitalMotorDriver.h"
#include "AnalogMotorDriver.h"
#include "AccelMotorDriver.h"

// 2つのモーターを制御する場合の例 //
constexpr uint8_t pins1[] = {17, 16};
constexpr uint8_t pins2[] = {14, 15};
constexpr uint8_t pin3[] = {32, 32};

DigitalMotor test1(pins1);
AnalogMotor test2(pins2);
AccelMotor test3(pin3, 10);

void setup() {
  test1.begin();
  test2.begin();
  test3.begin();
}

void loop() {
  static long steps= 0;
  static int speed = 0;
  static int direc = 1;

  if(steps == 10) {
    test1.write(direc);
    test2.write(speed * direc);
    steps = 0;
  }
  test3.write(speed * direc);
  delay(5);

  speed += (speed < 250 ? 50 : -speed);
  if (!speed)
    direc *= -1;
}