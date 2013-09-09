#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/**
	LCD backlight colors
*/
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// Number or color modes  
#define MAX_COLOR_MODE_COUNT 9

// Maximum length of the string for the display item
#define LABEL_LENGTH 10

const byte DIRECTION_STOP = 0;
const byte DIRECTION_FORWARD = 1;
const byte DIRECTION_BACKWARD = 2;

#endif
