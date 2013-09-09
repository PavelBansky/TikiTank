// RunningColorEffect.h

#ifndef _RUNNINGCOLOREFFECT_h
#define _RUNNINGCOLOREFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Running Color Effect

	Program displays running solid color light on the tank cannon
*/
class RunningColorEffect : public IProgram
{
 public:
	 RunningColorEffect(LPD8806 *ledStrip, uint32_t *clrs, bool automatic);
	 virtual void init();
	 virtual void step();
	 virtual int getRotationPeriod() { return 3000; }
	 virtual byte getModeCount() { return MAX_COLOR_MODE_COUNT; }
	 virtual void setMode(byte mode);
 private:
	void internalInit();
	void changeModeColor();
	LPD8806 *strip;	
	byte activeMode;
	short position;
	byte sleepDelay;
	short cnt;
	bool cleaning;
	bool autoMode;

	uint32_t activeColor;
	uint32_t *colors;
};

#endif

