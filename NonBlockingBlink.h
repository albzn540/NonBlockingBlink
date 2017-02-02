/*
*  Blink your LED without blocking your other code!
*
*  Author: Albin Winkelmann
*    Date: 15.12.2016 - 00:36
*/

#ifndef NonBlockingBlink_h
#define NonBlockingBlink_h

#include "Arduino.h"

class NonBlockingBlink {
public:
  NonBlockingBlink(uint8_t led, uint8_t times, uint8_t groundstate);
  NonBlockingBlink(uint8_t led, uint8_t groundstate);
  void setBlinkTimes(uint8_t times);
  void setBlinkForever();
  void stopBlink();
  void setInterval(long millis);
  void update();

private:
  uint8_t led;
  int times;
  uint8_t groundstate;
  uint8_t ledstate;
  bool forever;
  unsigned long previousMillis;
  unsigned long interval;

};

#endif
