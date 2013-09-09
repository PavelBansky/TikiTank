#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IProgram.h"
#include "View.h"

const byte STATE_IDLE = 1;			// Auto program is in idle mode  (screen saver)
const byte STATE_RUNNING = 0;		// Auto program is running

/*
Controller class is the main class that process inputs from user and sensors,
in order to changes the light effect and its behavior.

Controller class contains array of effects and is responsible for effect switching
based on outside events.
*/
class Controller
{
 public:
	// Constructor
	Controller(IProgram *pprograms[], byte prgCount, byte idleIndex, long idleTout, View *pview);
	// Initialization of inputs and outputs
	void init();
	// Main method to process all the events
	void processEvents();
 private:
	// Process events based on the serial data
	void processEvents(byte serialData);
	// Set given program (effect) as active
	void setProgram(byte program);
	// Change mode of the current program
	void changeMode();
	// Display given menu item
	void setMenuItem(byte index);
	// Set program argument value
	void setArgument(int arg);
	// Process button events
	void processButtons();

	byte menuPosition;
	byte activeProgram;	 
	byte programCount;
	byte activeMode;

	bool buttonsPressed;

	int programArg;
	int argMax;
	int argMin;

	unsigned long tickTimeout;
	volatile byte state;
	volatile long idleTimeout;
	byte idleProgram;

	HardwareSerial Uart;
	IProgram** programs;
	View *view;
};


