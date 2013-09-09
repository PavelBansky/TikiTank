// RainbowEffect.h

#ifndef _RAINBOWEFFECT_h
#define _RAINBOWEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Rainbow Effect

	Program displays runnin rainbow on the tank cannon
*/
class RainbowEffect : public IProgram
{
 public:
	 RainbowEffect(LPD8806 *ledStrip);
	 virtual void init();
	 virtual void step();
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	uint32_t wheel(uint16_t WheelPos);
	LPD8806 * strip;	
	short counter;
};

#endif

