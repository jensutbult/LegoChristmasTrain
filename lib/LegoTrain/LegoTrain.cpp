#include <stdlib.h>
#include "Arduino.h"
#include "LegoTrain.h"


#define MAX_SPEED 0x3
#define ACCELLERATION 1300
#define STOP_TIME 300 // Stay on station for 5 minutes

LegoTrain::LegoTrain(const PowerFunctions& train, uint8_t sensorPin) : _train(train)
{
  _train = train;
  _nextUpdateMillis = 0;
  _state = ACCELLERATING;
  _currentSpeed = 0x0;
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT);
}

void LegoTrain::sendState()
{
  _train.single_pwm(BLUE, _currentSpeed);
}

void LegoTrain::update()
{
  unsigned long currentMillis = millis();
  if (currentMillis < _nextUpdateMillis) { return; }

  switch(_state) {
    case ACCELLERATING:
      if (_currentSpeed >= MAX_SPEED) {
        _state = RUNNING;
        _nextUpdateMillis = 0;
        break;
      }
      _currentSpeed += 0x1;
      sendState();
      _nextUpdateMillis = currentMillis + ACCELLERATION;
      break;
    case RUNNING:
      _nextUpdateMillis = 0;
      if (digitalRead(_sensorPin) == HIGH) {
        _state = BREAKING;
        break;
      }
      break;
    case BREAKING:
      if (_currentSpeed <= 0x0) {
        _state = STOPPED;
        _nextUpdateMillis = currentMillis + 1000 * (uint32_t)STOP_TIME;
        break;
      }
      _currentSpeed -= 0x1;
      sendState();
      _nextUpdateMillis = currentMillis + ACCELLERATION;
      break;
    case STOPPED:
      _state = ACCELLERATING;
      _nextUpdateMillis = 0;
      break;
  }
}