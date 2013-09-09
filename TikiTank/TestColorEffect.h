// TestColorEffect.h

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

#define MAX_SOLID_COLOR_COUNT 9

struct Color {
	int32_t color;
	char name[LABEL_LENGTH];
};

/**
	Test Color Effect

	Program changes color of the LED strip based on user input
*/
class TestColorEffect : public IProgram
{
 public:
	 TestColorEffect(char name[], LPD8806 *ledStrip);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg);
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return MAX_SOLID_COLOR_COUNT-1; }	
	 virtual int getRotationPeriod() { return 0; }
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	LPD8806 * strip;	
	char name[LABEL_LENGTH];	
	short argument;

	Color colors[MAX_SOLID_COLOR_COUNT];
};

#endif

