#ifndef __BLYNKGO_DUINO_H__
#define __BLYNKGO_DUINO_H__

#include <Arduino.h>
#include "src/GTimerDuino.h"
#include "src/HWButton.h"
#include "src/CircularBuffer.h"
#include <EEPROM.h>

#if defined(__AVR_ATmega328P__)
  #define ARDUINO_UNO  // or NANO
  #define MCU_TYPE    "Arduino Uno/Nano"
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define ARDUINO_MEGA
  #define MCU_TYPE    "Arduino MEGA"
#elif defined( ESP8266)
  #define MCU_TYPE    "ESP8266"
#elif defined( ESP32)
  #define MCU_TYPE    "ESP32"
#else
  #define MCU_TYPE    "Unknown"
#endif

// #if defined ESP8266 || defined ESP32
//   #include "src/SoftwareSerial.h"
// #endif



#endif // __BLYNKGO_DUINO_H__
