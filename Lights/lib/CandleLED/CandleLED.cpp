#include <stdlib.h>
#include "CandleLED.h"
#include "Arduino.h"


CandleLED::CandleLED(uint8_t pin, lightType type, float intensity) {
  _pin = pin;
  _isFlashing = false;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _nextUpdateMillis = millis();
  _intensity = intensity;
  _type = type;
}

CandleLED::CandleLED(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _nextUpdateMillis = millis();
  _intensity = 0.5;
  _type = CANDLE;
}

CandleLED::CandleLED(uint8_t pin, lightType type) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _nextUpdateMillis = millis();
  _intensity = 0.5;
  _type = type;
}

void CandleLED::update() {
  uint32_t currentMillis = millis();
  if ((int16_t)(currentMillis - _nextUpdateMillis) < 0) { return; }
  
  if (_isFlashing) {
    if (_intensity == 0) {
      _intensity = 250;
      _nextUpdateMillis = currentMillis + 50;
    } else {
      _intensity = 0;
      _nextUpdateMillis = currentMillis + 1000;
    }
    analogWrite(_pin, _intensity);
    return;
  }

  uint8_t flickering;
  switch(_type) {
    case FIRE:
      flickering = 100;
      break;
    case CANDLE:
      flickering = 60;
      break;
    case LIGHTBULB:
      flickering = 20;
      break;
  }
  uint8_t base = 255 - flickering;
  analogWrite(_pin, _intensity * (random(flickering)+base));
  _nextUpdateMillis = currentMillis + random(300);
}

void CandleLED::flash(bool enabled) {
    _isFlashing = enabled;
}
