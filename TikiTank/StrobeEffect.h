#ifndef _STROBEEFFECT_h
#define _STROBEEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Strobe Effect

	Ummmm, I guess this is a strobe effect
*/
class StrobeEffect : public IProgram
{
 public:
	 StrobeEffect(char programName[], LPD8806 *ledStrip, uint32_t *clrs);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg);
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return 1; }
	 virtual int getRotationPeriod() { return 1500; }
	 virtual byte getModeCount() { return MAX_COLOR_MODE_COUNT; }
	 virtual void setMode(byte mode);

 private:
	LPD8806 * strip;	
	char name[LABEL_LENGTH];	
	byte activeMode;
	short argument;
	byte speed;
	boolean lightSwitch;

	uint32_t *colors;
};

#endif

