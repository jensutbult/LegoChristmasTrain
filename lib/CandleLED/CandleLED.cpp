#include <stdlib.h>
#include "CandleLED.h"
#include "Arduino.h"

CandleLED::CandleLED(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _nextUpdateMillis = millis();
}

void CandleLED::update()
{
  uint32_t currentMillis = millis();
  if ((int16_t)(currentMillis - _nextUpdateMillis) < 0) { return; }
  analogWrite(_pin, random(80)+100);
  _nextUpdateMillis = currentMillis + random(300);
}
