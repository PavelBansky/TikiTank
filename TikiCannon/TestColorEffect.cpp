#include "TestColorEffect.h"


/**
 Constructor

 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
*/
TestColorEffect::TestColorEffect(LPD8806 *ledStrip, uint32_t *clrs)
{	
	strip = ledStrip;	
	colors = clrs;
	activeMode = 0;
}

void TestColorEffect::init()
{
	strip->solidColor(colors[activeMode]);
} 

void TestColorEffect::step()
{	
	strip->show();	
	delay(10);
}

void TestColorEffect::setMode(byte mode)
{
	if (mode >= 0 && mode < MAX_COLOR_MODE_COUNT)
	{
		activeMode = mode;
		init();
	}
}

