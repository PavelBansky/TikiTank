#include "View.h"

/**
 Constructor
*/
View::View()
{
	backlightColor = TEAL;
}

/**
	Initialization of the LCD display
*/
void View::init()
{
	lcd = Adafruit_RGBLCDShield();
	lcd.clear();
	lcd.begin(16, 2);
	lcd.setBacklight(backlightColor);
	lcd.print("Starting...");
}

/** 
	Read status of the buttons

	@result		bit field with state of each button
*/
uint8_t View::readLCDButtons()
{	
	return lcd.readButtons();
}

/**
	Display given string as an active menu item

	@param		name	Caption of the menu item
*/
void View::setMenuItem(char *name)
{
	strncpy(menuItem, name, sizeof(menuItem));
	updateMenu();
}

/**
	Display given string as an active program

	@param		name	Program name
*/
void View::setProgram(char *name)
{
	strncpy(programName, name, sizeof(programName));	
	lcd.clear();	
	updateMenu();
	updateStatusBar();
}

/**
	Display given string as an argument

	@param		arg	argument value
*/
void View::setArgument(char *arg)
{
	strncpy(argStr, arg, sizeof(argStr));		
	updateStatusBar();
}

/**
	Blink the display to show error or warning
*/
void View::errorBlink() 
{
	lcd.setBacklight(YELLOW);
	delay(50);
	lcd.setBacklight(backlightColor);
}

/**
	Redraw menu items
*/
void View::updateMenu()
{
	lcd.setCursor(0,1);
	lcd.print("[ ");	
	lcd.print(menuItem);	
	for(int i=0; i < (13 - strlen(menuItem)); i++)
		lcd.print(" ");
	lcd.print("]");
}

/**
	Redraw statu bar with active program and argument
*/
void View::updateStatusBar()
{
	lcd.setCursor(0,0);
	lcd.print(programName);	

	lcd.setCursor(10, 0);
	lcd.print("   ");
	lcd.setCursor(16 - strlen(argStr), 0);
	lcd.print(argStr);	
}





