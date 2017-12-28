#include "Arduino.h"
#include "LegoTrain.h"


#define MAX_SPEED 200
#define STOP 0
#define ACCELLERATION 30
#define STOP_TIME 60 // Stay on station for 1 minute

LegoTrain::LegoTrain(uint8_t throttlePin, uint8_t directionPin, uint8_t enabledPin, uint8_t sensorPin) {
  _nextUpdateMillis = 0;
  _state = ACCELERATING;
  _currentSpeed = STOP;
  _throttlePin = throttlePin;
  _directionPin = directionPin;
  _enabledPin = enabledPin;
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT);
}

void LegoTrain::enabled(bool enabled) {
  digitalWrite(_enabledPin, enabled);
}

void LegoTrain::update() {
  uint32_t currentMillis = millis();
  if ((int32_t)(currentMillis - _nextUpdateMillis) < 0) { return; }

  switch(_state) {
    case ACCELERATING:
      if (_currentSpeed == MAX_SPEED) {
        _state = RUNNING;
        break;
      }
      _currentSpeed++;
      analogWrite(_throttlePin, _currentSpeed);
      _nextUpdateMillis = currentMillis + ACCELLERATION;
      break;
    case RUNNING:
      if (analogRead(_sensorPin) < 20) {
        _state = BREAKING;
      }
      break;
    case BREAKING:
      if (_currentSpeed == STOP) {
        _state = STOPPED;
        _nextUpdateMillis = currentMillis + 1000 * (uint32_t)STOP_TIME;
        break;
      }
      _currentSpeed--;
      analogWrite(_throttlePin, _currentSpeed);
      _nextUpdateMillis = currentMillis + ACCELLERATION;
      break;
    case STOPPED:
      _state = ACCELERATING;
      break;
  }
}
