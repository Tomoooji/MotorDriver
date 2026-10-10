// 基本的な使用方法 //

#include "AnalogMotorDriver.h"
#include "DigitalMotorDriver.h"

// 2つのモーターを制御する場合の例 //
constexpr uint8_t pins1[] = {17, 16};
constexpr uint8_ pins2[] = {14, 15};

AnalogMotor test1(pins1);
DigitalMotor test2(pins2);

int speed;
int direc = 1;

void setup() {
  test1.begin();
  test2.begin();
}

void loop() {
  test1.write(direc);
  test2.write(speed * direc);
  delay(500);
  speed += (speed < 250 ? 50 : -speed);
  if (!speed)
    direc *= -1;
}