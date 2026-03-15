#include <AnalogMotorDriver.h>
#include <DigitalMotorDriver.h>

AnalogMotor test1;
DigitalMotor test2;
constexpr uint8_t pins1[]={17,16};
constexpr uint8_t pins2[]={14,15};
int speed;
int direc=1;

void setup(){
  test1.attach(pins1);
  test2.attach(pins2);
}

void loop(){
  test1.move(speed*direc);
  test1.move(direc);
  delay(500);
  speed += (speed < 250? 50: -speed);
  if(!speed)direc*=-1;
}