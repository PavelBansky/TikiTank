#include "RunningColorEffect.h"

/**
 Constructor

 @param		ledStrip	pointer to LED strip controlling class	 
 @param		clrs		pointer to array of colors for color modes
 @param		automatic	automatic color mode change
*/
RunningColorEffect::RunningColorEffect(LPD8806 *ledStrip, uint32_t *clrs, bool automatic)
{	
	strip = ledStrip;	
	colors = clrs;
	activeMode = 0;
	autoMode = automatic;
	cleaning = false;
}

void RunningColorEffect::init()
{
	strip->solidColor(strip->Color(0, 0, 0));
	strip->show();
	internalInit();
}

void RunningColorEffect::internalInit()
{
	if (cleaning)
	{
		activeColor = strip->Color(0, 0, 0);
		if (autoMode)
			changeModeColor();
	}
	else
		activeColor = colors[activeMode];

	position = 0;
	cnt = 0;
	sleepDelay = 12;
}

void RunningColorEffect::step()
{	
	strip->setPixelColor(position, activeColor);
	strip->show();

	cnt++;
	if (cnt > (strip->numPixels() / 3))
	{
		cnt=0;
		sleepDelay /= 2;
	}

	if (sleepDelay <=0) sleepDelay = 1;
	delay(sleepDelay);
	
	position++;

	// clean after end
	if (position > strip->numPixels())
	{
		cleaning = (cleaning) ? false : true;

		internalInit();
	}
}

void RunningColorEffect::setMode(byte mode)
{
	if (mode >= 0 && mode < getModeCount())
	{
		activeMode = mode;
		init();
	}
}

void RunningColorEffect::changeModeColor()
{
	activeMode++;
	if (activeMode >= getModeCount())
	{
		activeMode = 0;
	}
}


