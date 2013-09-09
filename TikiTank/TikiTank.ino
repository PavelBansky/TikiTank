/**
* Tiki Tank 1.0
* http://www.tikitank.com/
* 
* This is the firmware for the main CPU that controls tank threads.
* 
* Intended CPU: Teensy++ 2.0
*
*/
#include "AutoThreadEffect.h"
#include "EffectRotator.h"
#include "RainbowEffect.h"
#include "TestColorEffect.h"
#include "StrobeEffect.h"
#include "Constants.h"
#include <Wire.h>
#include "SPI.h"
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>
#include <LPD8806.h>
#include "Controller.h"
#include "View.h"
#include "ThreadEffect.h"
#include "SolidColorEffect.h"

// Length of the LED strip for thread
const int stripLength = (5 * 32)*3;
// Number of programs (effects)
const int programCount = 7;
// Idle effect
const byte idleEffect = 3;
// Idle timeout
const int idleTimeout = 60000;


// Main array with programs (effects)
IProgram *programs[programCount];
uint32_t colors[MAX_COLOR_MODE_COUNT];

LPD8806 strip = LPD8806(stripLength); 
AutoThreadEffect autoProgram	= AutoThreadEffect("Auto",  &strip, colors);
ThreadEffect manualProgram	= ThreadEffect("Manual", -10, 10, &strip, colors);

SolidColorEffect solidColor = SolidColorEffect("Colors", &strip, colors);
RainbowEffect rainbow = RainbowEffect("Rainbow", &strip);
StrobeEffect strobe = StrobeEffect("Strobe", &strip, colors);

TestColorEffect testColor = TestColorEffect("Test", &strip);
EffectRotator effectRotator = EffectRotator("FX rotate", programs, programCount); 

View view = View();
Controller controller = Controller(programs, programCount, idleEffect, idleTimeout, &view);

void setup() {	
	strip.begin();

	programs[0] = &autoProgram;
	programs[1] = &manualProgram;
	programs[2] = &effectRotator;
	programs[3] = &rainbow;
	programs[4] = &solidColor;
	programs[5] = &strobe;
	programs[6] = &testColor;

	colors[0] = strip.Color(127, 127, 127);	// White
	colors[1] = strip.Color(127, 10, 73);	// Pink
	colors[2] = strip.Color(63, 0, 63);		// Purple
	colors[3] = strip.Color(0, 0, 127);		// Blue
	colors[4] = strip.Color(0, 127, 127);	// Aqua
	colors[5] = strip.Color(0, 127, 0);		// Green
	colors[6] = strip.Color(127, 127, 0);	// Yellow
	colors[7] = strip.Color(127, 0, 0);		// Red	
	colors[8] = strip.Color(64, 0, 0);		// Dark red

	view.init();	

	// Wait for SensorDuino to initializem because the MOSI and CLK of Teensy are connected
	// Initialization sequence of SensorDuino sends some crap on SPI, causing the lights to be confused
	delay(4000); 
	
	controller.init();
}

void loop() 
{   
	controller.processEvents();
}  


