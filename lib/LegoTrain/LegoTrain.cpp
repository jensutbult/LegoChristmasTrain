#include "Arduino.h"
#include "LegoTrain.h"


#define MAX_SPEED 3
#define STOP 0
#define ACCELLERATION 500
#define STOP_TIME 300 // Stay on station for 5 minutes

LegoTrain::LegoTrain(const PowerFunctions& train, uint8_t sensorPin) : _train(train) {
  _train = train;
  _nextUpdateMillis = 0;
  _state = ACCELERATING;
  _currentSpeed = STOP;
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT);
}

void LegoTrain::sendState() {
  _train.single_pwm(BLUE, _speeds[_currentSpeed]);
}

void LegoTrain::update() {
  uint32_t currentMillis = millis();
  if ((int32_t)(currentMillis - _nextUpdateMillis) < 0) { return; }

  switch(_state) {
    case ACCELERATING:
      if (_currentSpeed == MAX_SPEED) {
        _state = RUNNING;
        _nextUpdateMillis = currentMillis + 5000;
        break;
      }
      _currentSpeed++;
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
      if (_currentSpeed == STOP) {
        _state = STOPPED;
        _nextUpdateMillis = currentMillis + 1000 * (uint32_t)STOP_TIME;
        break;
      }
      _currentSpeed--;
      sendState();
      _nextUpdateMillis = currentMillis + ACCELLERATION;
      break;
    case STOPPED:
      _state = ACCELERATING;
      _nextUpdateMillis = 0;
      break;
  }
}
