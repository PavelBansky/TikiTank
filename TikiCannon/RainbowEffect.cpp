#include "RainbowEffect.h"

/**
 Constructor

 @param		ledStrip	pointer to LED strip controlling class	 
*/
RainbowEffect::RainbowEffect(LPD8806 *ledStrip)
{	
	strip = ledStrip;	
}

void RainbowEffect::init()
{
	counter = 0;
} 

void RainbowEffect::step()
{	
  uint16_t i;

    for (i=0; i < strip->numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color
      // wheel (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
		strip->setPixelColor((strip->numPixels() -1)- i, wheel(((i * 384 / strip->numPixels()) + counter) % 384));
    }
    strip->show();   // write all the pixels out

	//cycles of all 384 colors in the wheel
	counter = (counter < 384) ? counter+1 : 0;
	delay(1);
}

/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g - b - back to r

uint32_t RainbowEffect::wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128; // red down
      g = WheelPos % 128;       // green up
      b = 0;                    // blue off
      break;
    case 1:
      g = 127 - WheelPos % 128; // green down
      b = WheelPos % 128;       // blue up
      r = 0;                    // red off
      break;
    case 2:
      b = 127 - WheelPos % 128; // blue down
      r = WheelPos % 128;       // red up
      g = 0;                    // green off
      break;
  }
  return(strip->Color(r,g,b));
}

