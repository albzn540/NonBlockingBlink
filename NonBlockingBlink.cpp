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
  blinking = false;
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
  blinking = false;
}

void NonBlockingBlink::setBlinkTimes(uint8_t times){
  this->times = times * 2;
  blinking = true;
}

void NonBlockingBlink::setBlinkForever(){
  forever = true;
  blinking = true;
  times = 0;
}

void NonBlockingBlink::stopBlink(){
  forever = false;
  blinking = false;
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
    if(!blinking) digitalWrite(led, groundstate);
  }

  else if(blinking){
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      Serial.print("Time: ");
      Serial.print(times);
      Serial.print("               State before change: ");
      Serial.println(ledstate);

      digitalWrite(led, !ledstate);
      ledstate = !ledstate;
      times--;
    }
    if(times == 0) {
      blinking = false;
      digitalWrite(led, groundstate);
      Serial.println(groundstate);
    }
  }
}
