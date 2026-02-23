#ifndef MOTORDRIVER_PINCONFIG_H
#define MOTORDRIVER_PINCONFIG_H

#include <Arduino.h>

#if defined(ESP32)
//  constexpr int DIGITALPINNUM = 0;
  constexpr uint8_t _DIGITALPINS[];
//  constexpr int INPUTPINNUM = 4;
  constexpr uint8_t _INPUTPINS[] = {34, 35, 36, 39};
  
#elif defined(ARDUINO_ARCH_AVR)
//#else
//  constexpr int DIGITALPINNUM = 8;
  constexpr uint8_t _DIGITALPINS[] = {0, 1, 2, 4, 7, 8, 12, 13};//{3, 5, 6, 9, 10, 11};
//  constexpr int INPUTPINNUM = 8;
  constexpr uint8_t _INPUTPINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
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