#ifndef VIEW_h
#define VIEW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_RGBLCDShield.h>
#include "Constants.h"

/*
View class is an abstraction layer for LCD and button hardware,
*/
class View
{
 public:
	// Constructor
	View();
	// Initialization of the LCD
	void init();
	// Display given string as active menu item
	void setMenuItem(char *name);
	// Display given string as active program
	void setProgram(char *name);
	// Display given string as a active program argument
	void setArgument(char *arg);
	// Blink the display as warning/error
	void errorBlink();		
	// Read status of the hardware buttons
	uint8_t readLCDButtons();

	int argument;	

 private:		
	// Redraw menu items
	void updateMenu();
	// Redraw statu bar with active program and argument
	void updateStatusBar();


	byte backlightColor;
	char menuItem[LABEL_LENGTH];
	char programName[LABEL_LENGTH];
	char argStr[LABEL_LENGTH];

	Adafruit_RGBLCDShield lcd;
};


#endif

