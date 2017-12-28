#ifndef CandleLED_h
#define CandleLED_h

#include <stdio.h>
#include "Arduino.h"


enum lightType {
  FIRE,
  CANDLE,
  LIGHTBULB
};

class CandleLED {
	public:
    CandleLED(uint8_t);
		CandleLED(uint8_t, lightType);
		CandleLED(uint8_t, lightType, float);
    void update();
    void flash(bool);
  private:
    uint8_t _pin;
    uint32_t _nextUpdateMillis;
		float _intensity;
		uint8_t _type;
    bool _isFlashing;
};

#endif
