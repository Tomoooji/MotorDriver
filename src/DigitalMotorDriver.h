#pragma once

class DigitalMotor{
 private:
  const uint8_t* _pins = nullptr;
  int _direction = 0;
 public:
  DigitalMotor(){}
  void attach(const uint8_t pins[]){
    this->_pins = pins;
    pinMode(this->_pins[0], OUTPUT);
    pinMode(this->_pins[1], OUTPUT);
  }
  void move(int direction){
    this->_direction = constrain(direction, -1, 1);
    digitalWrite(this->_pins[0], this->_direction>0);
    digitalWrite(this->_pins[1], this->_direction<0);
  }
  uint8_t pin(const uint8_t idx){return this->_pins[idx];}
  int direction(){return this->_direction;}
};
