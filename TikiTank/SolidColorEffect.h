#ifndef _SOLIDCOLOREFFECT_h
#define _SOLIDCOLOREFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Solid Color Effect

	Program periodically changes color of the LED strip
*/
class SolidColorEffect : public IProgram
{
 public:
	 SolidColorEffect(char name[], LPD8806 *ledStrip, uint32_t *clrs);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg);
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return 0; }
	 virtual int getRotationPeriod() { return 3000; }
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	LPD8806 * strip;	
	char name[LABEL_LENGTH];	
	short argument;
	short direction;

	uint32_t *colors;
};

#endif

