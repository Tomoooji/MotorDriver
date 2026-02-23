// ESP32 でモータードライバーL298Nを制御する //

#include <MotorDriver.h>

struct L298N_ESP32{
  ESP32MotorDriver3pin A;
  ESP32MotorDriver3pin B;
} L298N;

void setup(){
  L298N.A.attach(9,8,10);
  L298N.B.attach(7,6,5);
  L298N.A.setSpeed(255);
  L298N.B.setSpeed(255);
}

void loop(){
  L298N.A.forward();
  L298N.B.forward();
  delay(1000);
  L298N.A.stop();
  L298N.B.stop();
  delay(500);
  L298N.A.backward();
  L298N.B.backward();
  delay(1000);
}
