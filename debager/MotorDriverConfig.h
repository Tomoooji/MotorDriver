#ifndef MOTORDRIVER_CONFIG_H
#define MOTORDRIVER_CONFIG_H

#include <Arduino.h>

#if defined(ESP32)
  constexpr uint8_t _DIGITALPINS[] = {};
  constexpr uint8_t _INPUTPINS[] = {34, 35, 36, 39};
  constexpr int ESPPWMFreq = 12800;
  constexpr uint8_t DEFAULTPWMPIN = 15;

#elif defined(ARDUINO_ARCH_AVR)
  constexpr uint8_t _DIGITALPINS[] = {0, 1, 2, 4, 7, 8, 12, 13};//{3, 5, 6, 9, 10, 11};
  constexpr uint8_t _INPUTPINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
  constexpr uint8_t DEFAULTPWMPIN = 11;
//#else
#endif


inline bool isInputOnly(uint8_t pin){
  for(uint8_t inputpin : _INPUTPINS){
    if(pin == inputpin) return true;
  }
  return false;
}

inline bool isDigitalOnly(uint8_t pin){
  for(uint8_t digitalpin : _DIGITALPINS){
    if(pin == digitalpin) return true;
  }
  return false;
}


#endif