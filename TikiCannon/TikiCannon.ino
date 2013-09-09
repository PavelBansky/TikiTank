/**
* Tiki Tank Cannon 1.0
* http://www.tikitank.com/
* 
* This is the firmware for the CPU that controls tank cannon
* 
* Intended CPU: ATMega 328
*
*/
#include "RunningColorEffect.h"
#include "CannonBallEffect.h"
#include "RainbowEffect.h"
#include "TestColorEffect.h"
#include "SolidColorEffect.h"
#include "SPI.h"
#include <LPD8806.h>
#include "IProgram.h"

// Number of LEDs in the LED strip
const int stripLength = 77;

// PIN for program change button
const int programButton = 5;
// PIN for mode change button
const int modeButton = 6;
// PIN for trigger button
const int triggerButton = 7;

uint32_t colors[MAX_COLOR_MODE_COUNT];
LPD8806 strip = LPD8806(stripLength); 
IProgram* mainProgram;

byte activeProgram;	 
byte activeMode;
bool buttonsPressed;


void setup()
{
	pinMode(programButton, INPUT);
	pinMode(modeButton, INPUT);
	pinMode(triggerButton, INPUT);

	strip.begin();

	activeProgram = 0;
	activeMode = 0;	
	buttonsPressed = false;

	// Color modes
	colors[0] = strip.Color(127, 127, 127);	// White
	colors[1] = strip.Color(127, 10, 73);	// Pink
	colors[2] = strip.Color(63, 0, 63);		// Purple
	colors[3] = strip.Color(0, 0, 127);		// Blue
	colors[4] = strip.Color(0, 127, 127);	// Aqua
	colors[5] = strip.Color(0, 127, 0);		// Green
	colors[6] = strip.Color(127, 127, 0);	// Yellow
	colors[7] = strip.Color(127, 0, 0);		// Red	
	colors[8] = strip.Color(64, 0, 0);		// Dark red

	setProgram(activeProgram);
}

void loop()
{
	// Step the effect
	mainProgram->step();

	// Evaluate button state
	uint8_t buttons = readButtons();

	if (buttons && !buttonsPressed)
	 {
		 if (buttons & BUTTON_PROGRAM) {
			changeProgram();	
		 }
		 else if (buttons & BUTTON_MODE)
		 {
			 changeMode();
		 }
		 else if (buttons & BUTTON_TRIGGER)
		 {
			 // Do the trigger effect
			 CannonBallEffect* ball = new CannonBallEffect(&strip);
			 ball->init();
			 ball->step();
			 free(ball);
			 // mainProgram->init();
		 }
		buttonsPressed = true;
	 }	
	else if (!buttons)
	{
		buttonsPressed = false;
	}
}

/**
	Instantiate appropriate effect class based on argument

	@param		program		program to instantiate
*/
void setProgram(byte program)
{
	free(mainProgram);

	switch (program)
	{
		case 1: 
			mainProgram = new RunningColorEffect(&strip, colors, false);
			break;
		case 2: 
			mainProgram = new RunningColorEffect(&strip, colors, true);
			break;
		case 3: 
			mainProgram = new TestColorEffect(&strip, colors);
			break;
		case 4: 
			mainProgram = new SolidColorEffect(&strip, colors);
			break;
		default:
			activeProgram = 0;
			mainProgram = new RainbowEffect(&strip);
			break;
	}

	mainProgram->init();	
}

/**
	Read button state

	@result		bitfield with the button states
*/
uint8_t readButtons()
{
	uint8_t buttons = 0;
	buttons |= (digitalRead(programButton) == LOW) ? BUTTON_PROGRAM : 0;
	buttons |= (digitalRead(modeButton) == LOW) ? BUTTON_MODE : 0;
	buttons |= (digitalRead(triggerButton) == LOW) ? BUTTON_TRIGGER : 0; 

	return buttons;
}

void changeProgram()
{
	activeProgram++;
	setProgram(activeProgram);
}

void changeMode()
{
	activeMode++;
	if (activeMode >= mainProgram->getModeCount())
	{
		activeMode = 0;
	}

	mainProgram->setMode(activeMode);
}

