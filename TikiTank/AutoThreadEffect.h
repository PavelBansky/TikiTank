// AutoThreadEffect.h

#ifndef _AUTOTHREADEFFECT_h
#define _AUTOTHREADEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Auto Thread Effect

	Program to control tank tread effect based on the data from speed sensor
*/
class AutoThreadEffect : public IProgram
{
 public:
	 AutoThreadEffect(char name[], LPD8806 *ledStrip, uint32_t *clrs);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return true; }
	 virtual void setArgument(short arg);
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return 1; }
	 virtual int getRotationPeriod() { return 0; }
	 virtual byte getModeCount() { return MAX_COLOR_MODE_COUNT; }
	 virtual void setMode(byte mode);
 private:
	LPD8806 * strip;	
	char name[LABEL_LENGTH];
	short argument;
	byte activeMode;
	byte direction;

	uint32_t *colors;
};

#endif

