#include "AutoThreadEffect.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
AutoThreadEffect::AutoThreadEffect(char programName[], LPD8806 *ledStrip, uint32_t *clrs)
{	
	strncpy(name, programName, sizeof(name));
	strip = ledStrip;	
	colors = clrs;

	activeMode = 0;
	setArgument(0);
}

void AutoThreadEffect::init()
{
	int32_t shortColor, longColor;

	shortColor = colors[activeMode];
	longColor = strip->Color(0, 0, 0);

	// draw the tank thread pattern
	strip->drawThread(shortColor, longColor);

	strip->show();
}

void AutoThreadEffect::step()
{
	if (direction == DIRECTION_FORWARD)
		strip->rotateRight();
	else if (direction == DIRECTION_BACKWARD)
		strip->rotateLeft();

	strip->show();
}

void AutoThreadEffect::setArgument(short arg)
{
	argument = arg;
	if (argument == 0)
	{
		direction =  DIRECTION_FORWARD;
	}
	else
	{
		direction = DIRECTION_BACKWARD;
	}
}

void AutoThreadEffect::setMode(byte mode)
{
	if (mode >= 0 && mode < MAX_COLOR_MODE_COUNT)
	{
		activeMode = mode;
		init();
	}
}

void AutoThreadEffect::getArgumentText(char *output)
{
	char outstr[LABEL_LENGTH] = "";

	if (argument == 0)
		strcat(outstr, "Forward");	
	else
		strcat(outstr, "Reverse");	

	strncpy(output, outstr, sizeof(outstr));	
}

void AutoThreadEffect::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}



