#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

// Bitmask for Trigger button
#define BUTTON_TRIGGER 0x04
// Bitmask for Mode button
#define BUTTON_MODE 0x02
// Bitmas for program button
#define BUTTON_PROGRAM 0x01

// Number or color modes  
#define MAX_COLOR_MODE_COUNT 9

#endif

