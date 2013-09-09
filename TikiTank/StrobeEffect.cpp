#include "StrobeEffect.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
StrobeEffect::StrobeEffect(char programName[], LPD8806 *ledStrip, uint32_t *clrs)
{	
	strncpy(name, programName, sizeof(name));
	strip = ledStrip;	
	colors = clrs;

	activeMode = 0;
	argument = 0;
	speed = 5;
	lightSwitch = true;
}

void StrobeEffect::init()
{
	strip->solidColor(colors[activeMode]);

	strip->show();	
}

void StrobeEffect::step()
{	
	uint32_t color;
	if (lightSwitch)
	{
		delay(speed);
		color = strip->Color(0, 0, 0);
		lightSwitch = false;
	}
	else
	{
		delay(speed*3);
		color = colors[activeMode];
		lightSwitch = true;
	}

	strip->solidColor(color);

	strip->show();		
}

void StrobeEffect::setMode(byte mode)
{
	if (mode >= 0 && mode < MAX_COLOR_MODE_COUNT)
	{
		activeMode = mode;
		init();
	}
}

void StrobeEffect::setArgument(short arg)
{
	argument = arg;	
	if (argument == 0)
		speed = 20;
	else
		speed = 25;
}

void StrobeEffect::getArgumentText(char *output)
{		
	char outstr[LABEL_LENGTH] = "";

	if (argument == 0)
		strcat(outstr, "Fast");	
	else
		strcat(outstr, "Slow");	

	strncpy(output, outstr, sizeof(outstr));	
}

void StrobeEffect::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}




