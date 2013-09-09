#include "CannonBallEffect.h"

/**
 Constructor

 @param		ledStrip	pointer to LED strip controlling class	 
*/
CannonBallEffect::CannonBallEffect(LPD8806 *ledStrip)
{	
	strip = ledStrip;	
}

void CannonBallEffect::init()
{
	strip->solidColor(strip->Color(0, 0, 0));
	strip->show();
} 

void CannonBallEffect::step()
{	
	// Cannon ball
	byte cnt = 0;
	int sleepDelay;

	for(int j=0; j <= 4; j++)
	{
		sleepDelay = 12 - (j*2);
		for(int i=0; i <= strip->numPixels(); i++)
		{
			strip->setPixelColor(i, strip->Color(0, 32+i, 32+i));
			strip->show();

			cnt++;
			if (cnt > (strip->numPixels() / 3))
			{
				cnt=0;
				sleepDelay /= 2;
			}

			if (sleepDelay <=0) sleepDelay = 1;
			delay(sleepDelay);
		}

		strip->solidColor(strip->Color(0, 0, 0));
		strip->show();
	}

	// blast
	for(int i=0; i < 1; i++)
	{
		strip->solidColor(strip->Color(64, 0, 0));		// Dark red
		strip->show();
		delay(40);
		strip->solidColor(strip->Color(127, 0, 0));		// Red
		strip->show();
		delay(40);
		strip->solidColor(strip->Color(127, 64, 0));	// Orange
		strip->show();
		delay(40);
		strip->solidColor(strip->Color(127, 127, 0));	// Yellow
		strip->show();
		delay(40);
		strip->solidColor(strip->Color(127, 127, 64));	// Warm white
		strip->show();
		delay(40);
		strip->solidColor(strip->Color(127, 127, 127));	// White
		strip->show();
		delay(40);
	}
	delay(260);


	// pause after blast
	strip->solidColor(strip->Color(0, 0, 0));
	strip->show();
	//delay(200);
}




