// ThreadEffect.h

#ifndef _THREADEFFECT_h
#define _THREADEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Thread Effect

	Program to control tank thread effect based on the user input (manual mode)
*/
class ThreadEffect : public IProgram
{
 public:
	 ThreadEffect(char name[], int minArg, int maxArg, LPD8806 *ledStrip, uint32_t *clrs);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg);
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return argMin; }
	 virtual int getArgumentMax() { return argMax; }
	 virtual int getRotationPeriod() { return 0; }
	 virtual byte getModeCount() { return MAX_COLOR_MODE_COUNT; }
	 virtual void setMode(byte mode);
 private:
	LPD8806 * strip;	
	char name[LABEL_LENGTH];
	short pause;
	short argMax;
	short argMin;
	short argument;
	byte activeMode;
	byte direction;

	uint32_t *colors;
};

#endif