#include <AnalogMotorDriver.h>
#include <DigitalMotorDriver.h>

constexpr uint8_t pins1[] = {17, 16};
constexpr uint8_t pins2[] = {14, 15};
int speed;
int direc = 1;
AnalogMotor test1(pins1);
DigitalMotor test2(pins2);

void setup() {
  test1.begin();
  test2.begin();
}

void loop() {
  test1.write(speed * direc);
  test1.write(direc);
  delay(500);
  speed += (speed < 250 ? 50 : -speed);
  if (!speed)
    direc *= -1;
}