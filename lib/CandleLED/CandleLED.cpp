#include <stdlib.h>
#include "CandleLED.h"
#include "Arduino.h"

CandleLED::CandleLED(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void CandleLED::update()
{
  uint16_t currentMillis = millis();
  if (currentMillis < _nextUpdateMillis) { return; }
  analogWrite(_pin, random(80)+100);
  _nextUpdateMillis = currentMillis + random(300);
}
