#include "SolidColorEffect.h"

/**
 Constructor

 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
SolidColorEffect::SolidColorEffect(LPD8806 *ledStrip, uint32_t *clrs)
{	
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
