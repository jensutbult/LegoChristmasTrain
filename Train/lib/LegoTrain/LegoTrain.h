#ifndef LegoTrain_h
#define LegoTrain_h

#include <stdio.h>
#include <stdlib.h>

#include "Arduino.h"

enum trainStates {
  ACCELERATING,
  RUNNING,
  BREAKING,
  STOPPED
};

class LegoTrain
{
	public:
    LegoTrain(uint8_t, uint8_t, uint8_t, uint8_t);
    void update();
    void enabled(bool);
  private:
    enum trainStates _state;
    uint8_t _throttlePin;
    uint8_t _directionPin;
    uint8_t _enabledPin;
    uint8_t _sensorPin;
    uint32_t _nextUpdateMillis;

    uint8_t _currentSpeed;
};

#endif
