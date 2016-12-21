#ifndef LegoTrain_h
#define LegoTrain_h

#include <stdio.h>
#include "Arduino.h"
#include "PowerFunctions.h"

enum trainStates {
  ACCELLERATING,
  RUNNING,
  BREAKING,
  STOPPED
};

class LegoTrain
{
	public:
    LegoTrain(const PowerFunctions&, uint8_t);
    void update();
  private:
    void sendState();
    PowerFunctions _train;
    enum trainStates _state;
    uint8_t _sensorPin;
    uint32_t _nextUpdateMillis;
    uint8_t _currentSpeed;
};

#endif
