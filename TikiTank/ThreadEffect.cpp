#include "ThreadEffect.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		minArg		minimum thread roration speed (negative number represents opossite direction)
 @param		maxArg		maximum thread rotation speed
 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
ThreadEffect::ThreadEffect(char programName[], int minArg, int maxArg, LPD8806 *ledStrip, uint32_t *clrs)
{	
	strncpy(name, programName, sizeof(name));
	strip = ledStrip;	
	colors = clrs;

	argMin = minArg;
	argMax = maxArg;	

	activeMode = 0;
	setArgument(0);
}

void ThreadEffect::init()
{
	int32_t shortColor, longColor;

	// mode 0
	shortColor = colors[activeMode];
	longColor = strip->Color(0, 0, 0);

	// draw the tank thread pattern
	strip->drawThread(shortColor, longColor);

	strip->show();
}

void ThreadEffect::step()
{
	if (direction == DIRECTION_FORWARD)
		strip->rotateRight();
	else if (direction == DIRECTION_BACKWARD)
		strip->rotateLeft();

	if (direction != DIRECTION_STOP)
	{
		strip->show();
		delay(pause);
	}
}

void ThreadEffect::setArgument(short arg)
{
	argument = arg;
	if (argument == 0)
	{
		direction = DIRECTION_STOP;
	}
	else
	{
		if (argument > 0)
			direction = DIRECTION_FORWARD;
		else if (argument < 0)
			direction = DIRECTION_BACKWARD;

		pause = 60 / abs(argument);
	}
}

void ThreadEffect::setMode(byte mode)
{
	if (mode >= 0 && mode < MAX_COLOR_MODE_COUNT)
	{
		activeMode = mode;
		init();
	}
}

void ThreadEffect::getArgumentText(char *output)
{
	char buf[8 * sizeof(int) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];
	short n = abs(argument);

	*str = '\0';

	do {
		int m = n;
		n /= 10;
		char c = m - 10 * n;
		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	char outstr[LABEL_LENGTH] = "";
	if (argument < 0)
		strcat(outstr, "-");

	strcat(outstr, str);
	strcat(outstr, " mph");
	strncpy(output, outstr, sizeof(outstr));	
}

void ThreadEffect::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}

