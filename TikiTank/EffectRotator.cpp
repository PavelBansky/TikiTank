#include "EffectRotator.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		pprograms[]	array of programs for rotation	 
 @param		prgCount	number of programs in the array
*/
EffectRotator::EffectRotator(char programName[], IProgram *pprograms[], byte prgCount)
{
	strncpy(name, programName, sizeof(name));
	programs = pprograms;
	programCount = prgCount;
	effect = 0;
}

void EffectRotator::init()
{
	startTime = millis();

	while(programs[effect]->getRotationPeriod() == 0 )
	{ 
		effect++;
		if (effect >= programCount)
			effect = 0;
	}

	programs[effect]->init();
}


void EffectRotator::step()
{	
	if ((millis() - startTime) < programs[effect]->getRotationPeriod())
	{
		programs[effect]->step();
	}
	else
	{
		effect++;
		init();
	}
}


void EffectRotator::getArgumentText(char *output)
{		
	char outstr[LABEL_LENGTH] = "";
	strncpy(output, outstr, sizeof(outstr));	
}

void EffectRotator::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}


