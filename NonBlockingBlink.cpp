/*
*  Blink your LED without blocking your other code!
*
*  Author: Albin Winkelmann
*    Date: 15.12.2016 - 00:36
*/

#include "Arduino.h"
#include "NonBlockingBlink.h"

NonBlockingBlink::NonBlockingBlink(uint8_t led, uint8_t times, uint8_t groundstate) {
  pinMode(led, OUTPUT);
  digitalWrite(led, groundstate);
  this->groundstate = groundstate;
  this->led = led;
  this->times = times * 2;

  interval = 500;
  previousMillis = 0;
  ledstate = groundstate;
  forever = false;
}

NonBlockingBlink::NonBlockingBlink(uint8_t led, uint8_t groundstate) {
  pinMode(led, OUTPUT);
  digitalWrite(led, groundstate);
  this->groundstate = groundstate;
  this->led = led;
  this->times = 0;

  interval = 500;
  previousMillis = 0;
  ledstate = groundstate;
  forever = false;
}

void NonBlockingBlink::setBlinkTimes(uint8_t times){
  this->times = times * 2;
}

void NonBlockingBlink::setBlinkForever(){
  forever = true;
  times = 0;
}

void NonBlockingBlink::stopBlink(){
  forever = false;
  times = 0;
}

void NonBlockingBlink::setInterval(long millis){
  interval = millis;
}

void NonBlockingBlink::update() {
  unsigned long currentMillis = millis();

  if(forever) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      digitalWrite(led, !ledstate);
      ledstate = !ledstate;
    }
  }

  else if(times != 0){
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      digitalWrite(led, !ledstate);
      ledstate = !ledstate;
      times--;
    }
  }

  else {
    digitalWrite(led, groundstate);
  }

}
