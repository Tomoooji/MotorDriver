#ifndef MORTORDRIVER_3PIN_ESP32_H
#define MORTORDRIVER_3PIN_ESP32_H
#include <Arduino.h>
#include "MotorDriverBase.h"

class ESP32MotorDriver3pin : public MotorDriverBase{
  private:
    uint8_t _pinPWM = DEFAULTPWMPIN;
  public:
    using MotorDriverBase::MotorDriverBase;

    bool attach(uint8_t pin1, uint8_t pin2) override{
      return this->attach(pin1, pin2, this->_pinPWM);
    }

    bool attach(uint8_t pin1, uint8_t pin2, uint8_t pinPWM){
      MotorDriverBase::switchMode_impl(pin1, pin2);
      if(this->checkPin(pinPWM) == MODE_INVALID || this->_MODE == MODE_INVALID){
        return false;
      }else{
        this->_pin1 = pin1;
        this->_pin2 = pin2;
        this->_pinPWM = pinPWM;
        pinMode(this->_pin1, OUTPUT);
        pinMode(this->_pin2, OUTPUT);

        if(this->checkPin(pinPWM) == MODE_DIGITAL || this->_MODE == MODE_DIGITAL){
          pinMode(this->_pinPWM, OUTPUT);
          this->_MODE = MODE_DIGITAL;
        }else{
          ledcAttach(this->_pinPWM, ESPPWMFreq, 8);
          this->_MODE = MODE_ANALOG;
        }
        return true;
      }
    }

    int moveForward() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pinPWM, HIGH);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pinPWM, this->speed());
          break;
        case MODE_INVALID:
          return 0;
      }
      digitalWrite(this->_pin1, HIGH);
      digitalWrite(this->_pin2, LOW);
      return this->speed();
    }

    int moveBackward() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pinPWM, HIGH);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pinPWM, this->speed());
          break;
        case MODE_INVALID:
          return 0;
      }
      digitalWrite(this->_pin1, LOW);
      digitalWrite(this->_pin2, HIGH);
      return this->speed();
    }

    int stop() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pinPWM, LOW);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pinPWM, 0);
          break;
        case MODE_INVALID:
          return 0;
      }
      digitalWrite(this->_pin1, LOW);
      digitalWrite(this->_pin2, LOW);
      return 0;
    }

    int lock() override{
      switch(this->_MODE){
        case MODE_DIGITAL:
          digitalWrite(this->_pinPWM, HIGH);
          break;
        case MODE_ANALOG:
          ledcWrite(this->_pinPWM, this->speed());
          break;
        case MODE_INVALID:
          return 0;
      }
      digitalWrite(this->_pin1, HIGH);
      digitalWrite(this->_pin2, HIGH);
      return this->speed();
    }
};
/*
class ESPL298N{
  public:
    ESPMotorDriver3pin A, B;
};
*/

#endif