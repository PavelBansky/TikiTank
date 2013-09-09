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

	Program displays rotating rainbow on the tank thread
*/
class RainbowEffect : public IProgram
{
 public:
	 RainbowEffect(char name[], LPD8806 *ledStrip);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg) { return; }
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return 0; }
	 virtual int getRotationPeriod() { return 3000; }
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	 uint32_t wheel(uint16_t WheelPos);
	LPD8806 * strip;	
	char name[LABEL_LENGTH];	
	short counter;
};

#endif

