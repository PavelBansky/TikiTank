#ifndef _TESTCOLOREFFECT_h
#define _TESTCOLOREFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Test Color Effect

	Program changes color of the LED strip based on user input
*/
class TestColorEffect : public IProgram
{
 public:
	 TestColorEffect(LPD8806 *ledStrip, uint32_t *clrs);
	 virtual void init();
	 virtual void step();
	 virtual byte getModeCount() { return MAX_COLOR_MODE_COUNT; }
	 virtual void setMode(byte mode);
 private:
	LPD8806 * strip;	
	int activeMode;

	uint32_t *colors;
};

#endif

