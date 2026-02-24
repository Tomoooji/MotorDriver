#ifndef MORTORDRIVER_2PIN_ESP32_H
#define MORTORDRIVER_2PIN_ESP32_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class ESP32MotorDriver2pin : public MotorDriverBase{
  public:
    using MotorDriverBase::MotorDriverBase;

    bool attach(uint8_t pin1, uint8_t pin2) override{
      MotorDriverBase::switchMode_impl(pin1, pin2);
      switch(this->_MODE){
        case MODE_DIGITAL:
          this->_pin1 = pin1;
          this->_pin2 = pin2;
          pinMode(this->_pin1, OUTPUT);
          pinMode(this->_pin2, OUTPUT);
          return true;
        case MODE_ANALOG:
          this->_pin1 = pin1;
          this->_pin2 = pin2;
          ledcAttach(this->_pin1, ESPPWMFreq, 8);
          ledcAttach(this->_pin2, ESPPWMFreq, 8);
          return true;
        case MODE_INVALID:
          return false;
      }
    }

    int moveForward() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pin1, HIGH);
          digitalWrite(this->_pin2, LOW);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pin1, this->speed());
          ledcWrite(this->_pin2, 0);
          break;
        case MODE_INVALID:
          return 0;
      }
      return this->speed();
    }

    int moveBackward() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, HIGH);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pin1, 0);
          ledcWrite(this->_pin2, this->speed());
          break;
        case MODE_INVALID:
          return 0;
      }
      return this->speed();
    }

    int stop() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, LOW);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pin1, 0);
          ledcWrite(this->_pin2, 0);
          break;
        case MODE_INVALID:
          return 0;
      }
      return 0;
    }

    int lock() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pin1, HIGH);
          digitalWrite(this->_pin2, HIGH);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pin1, this->speed());
          ledcWrite(this->_pin2, this->speed());
          break;
        case MODE_INVALID:
          return 0;
      }
      return this->speed();
    }
};

#endif