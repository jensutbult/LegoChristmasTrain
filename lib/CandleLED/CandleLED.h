#ifndef CandleLED_h
#define CandleLED_h

#include <stdio.h>
#include "Arduino.h"

class CandleLED
{
	public:
    CandleLED(uint8_t);
    void update();
  private:
    uint8_t _pin;
    uint32_t _nextUpdateMillis;
};

#endif
