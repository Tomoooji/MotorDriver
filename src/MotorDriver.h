// Main header file of this library //
#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <Arduino.h>
#include "MotorDriverBase.h"

#if defined(ESP32)
  #include "ESP32MotorDriver2pin.h"
  #include "ESP32MotorDriver3pin.h"
  
#elif defined(ARDUINO_ARCH_AVR)
//#else
  #include "MotorDriver2pin.h"
  #include "MotorDriver3pin.h"
#endif

#endif