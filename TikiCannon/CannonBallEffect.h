// CannonBallEffect.h

#ifndef _CANNONBALLEFFECT_h
#define _CANNONBALLEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LPD8806.h>
#include "IProgram.h"
#include "Constants.h"

/**
	Cannon Ball Effect

	Program for cannon shot and explosion effect
*/
class CannonBallEffect : public IProgram
{
 public:
	 CannonBallEffect(LPD8806 *ledStrip);
	 virtual void init();
	 virtual void step();
	 virtual byte getModeCount() { return 0; }
	 virtual void setMode(byte mode) { return; }
 private:
	uint32_t wheel(uint16_t WheelPos);
	LPD8806 * strip;	
	short counter;
};


#endif

