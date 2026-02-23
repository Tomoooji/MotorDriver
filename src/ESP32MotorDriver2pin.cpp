#if defined(ESP32)
#include "ESP32MotorDriver2pin.h"

void ESP32MotorDriver2pin::attach(uint8_t pin1, uint8_t pin2){
  this-> pin1 = pin1;
  this-> pin2 = pin2;
  ledcAttach(this-> pin1, 12800, 8);
  ledcAttach(this-> pin2, 12800, 8);
}
void ESP32MotorDriver2pin::forward(){
  ledcWrite(this-> pin1, this-> speed);
  ledcWrite(this-> pin2, 0);
}

void ESP32MotorDriver2pin::backward(){
  ledcWrite(this-> pin1, 0);
  ledcWrite(this-> pin2, this-> speed);
}

void ESP32MotorDriver2pin::stop(){
  ledcWrite(this-> pin1, 0);
  ledcWrite(this-> pin2, 0);
}

void ESP32MotorDriver2pin::lock(){
  ledcWrite(this-> pin1, this-> speed);
  ledcWrite(this-> pin2, this-> speed);
}

#endif