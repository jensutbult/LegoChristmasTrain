#ifndef LegoTrain_h
#define LegoTrain_h

#include <stdio.h>
#include <stdlib.h>

#include "Arduino.h"
#include "PowerFunctions.h"

enum trainStates {
  ACCELERATING,
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
    uint8_t _speeds [4] = {0x0, 0xF, 0xE, 0xD};
    PowerFunctions _train;
    enum trainStates _state;
    uint8_t _sensorPin;
    uint32_t _nextUpdateMillis;
    uint8_t _currentSpeed;
};

#endif
