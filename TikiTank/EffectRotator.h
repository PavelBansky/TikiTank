// EffectRotator.h

#ifndef _EFFECTROTATOR_h
#define _EFFECTROTATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Effect Rotator 

	Program that periodically executes other effect 
*/
class EffectRotator : public IProgram
{
 public:
	 EffectRotator(char programName[], IProgram *pprograms[], byte max_program_number);
	 virtual void init();
	 virtual void step();
	 virtual bool isInterruptDriven() { return false; }
	 virtual void setArgument(short arg) { return; }
	 virtual void getArgumentText(char *output);
	 virtual void getName(char *programName);
	 virtual int getArgumentMin() { return 0; }
	 virtual int getArgumentMax() { return 0; }
	 virtual int getRotationPeriod() { return 0; }
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	char name[LABEL_LENGTH];	
	int argument;
	//byte speed;
	byte effect;
	byte programCount;
	unsigned long startTime;
	unsigned long elapsedTime;

	IProgram** programs;
};

#endif

