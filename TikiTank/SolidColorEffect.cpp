#include "SolidColorEffect.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
SolidColorEffect::SolidColorEffect(char programName[], LPD8806 *ledStrip, uint32_t *clrs)
{	
	strncpy(name, programName, sizeof(name));
	strip = ledStrip;	
	colors = clrs;

	argument = 0;
	direction = 1;
}

void SolidColorEffect::init()
{
	strip->solidColor(colors[argument]);
} 

void SolidColorEffect::step()
{	
	init();
	argument += direction;
	strip->show();	
	delay(100);

	if (argument >= MAX_COLOR_MODE_COUNT) 
	{
		direction=-1;
	}
	else if (argument <= 0)
	{
		direction=1;
	}
}

void SolidColorEffect::setArgument(short arg)
{
	argument = arg;
	// sanity check
	if (argument < 0)
		argument = 0;
	else if (argument >= MAX_COLOR_MODE_COUNT)
		argument = MAX_COLOR_MODE_COUNT-1;

	init();
}

void SolidColorEffect::getArgumentText(char *output)
{		
	char outstr[LABEL_LENGTH] = "";
	strncpy(output, outstr, sizeof(outstr));		
}

void SolidColorEffect::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}


