#include "ESP32MotorDriver2pin.h"

ESP32MotorDriver2pin leg1{,0,255};
const uint8_t pin1 = 15;
const uint8_t pin2 = 2;
int flag;

void setup() {
  Serial.begin(9600);
  leg1.attach(pin1, pin2);
  leg1.setVelocity(255);
  leg1.stop();//init
}

void loop() {
  Serial.println("-----------");
  //flag = leg1.setVelocity(250);
  flag = leg1.velocity();
  Serial.println(flag);
  leg1.moveBackward();
  delay(1000);
}
