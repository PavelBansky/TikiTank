#include "Controller.h"

/**
 Constructor

 @param		pprograms[]	pointer to array of programs 
 @param		prgCount	count of programs in the array	 
 @param		idleIndex	index of the program to be run when system is in idle
 @param		idleTout	system idle timeout
*/
Controller::Controller(IProgram *pprograms[], byte prgCount, byte idleIndex, long idleTout, View *pview)
{
	Uart = HardwareSerial();
	programs = pprograms;
	view = pview;
	programCount = prgCount;
	idleTimeout = idleTout;
	idleProgram = idleIndex;

	menuPosition = 0;
	activeProgram = 0;
	activeMode = 0;
	programArg = 0;
	buttonsPressed = false;
	state = STATE_RUNNING;
}

/**
	Initialization of inputs and outputs
*/
void Controller::init()
{	
	Uart.begin(9600);
	setProgram(activeProgram);
	setMenuItem(menuPosition);	
}

/**
	Process inputs and change outputs.

	Reads data from sensor on the serial port and pass it on for processing
*/
void Controller::processEvents()
{
	// Data to be read from serial port
	byte serialData = 0;

	// Read serial data
	if (Uart.available() > 0)
	{
		serialData = Uart.read();
		// clear other data in buffer so we always have fresh one
		Uart.clear();
	}

	processEvents(serialData);
}

/**
 Process all events.

 Process speed sensor values, buttons and chnage effect appropriatelly

 @param		serialData	data from speed sensor
*/
void Controller::processEvents(byte serialData)
{	
	// If it's interrupt driven program, make sure you check timeout and step the right program
	if (programs[activeProgram]->isInterruptDriven())
	{
		// Step regular program based on the speed in serial data
		if (state == STATE_RUNNING && serialData > 0)
		{
			programs[activeProgram]->step();
			delay(serialData);
			tickTimeout = millis();
		}

		// Initiatie idle program if the idle timeout is reached
		if (state == STATE_RUNNING && (millis() - tickTimeout) > idleTimeout)
		{
			state = STATE_IDLE;
			programs[idleProgram]->init();
		}

		// Step idle program instead of normal program
		if (state == STATE_IDLE)
		{
			programs[idleProgram]->step();
		}

		// Resume standard program if IDLE program is interrupted by serial data
		if (state == STATE_IDLE && serialData > 0)
		{
			programs[activeProgram]->init();
			state = STATE_RUNNING;
		}

	}
	// otherwise step current program
	else 
	{
		programs[activeProgram]->step();
	}

	processButtons();
}

/**
 Read buttons state and make necessary apply changes to the UI

*/
void Controller::processButtons()
{
	uint8_t buttons = view->readLCDButtons();

	if (buttons && !buttonsPressed)
	 {
		// LEFT and RIGHT scroll through programs
		if (buttons & BUTTON_RIGHT) {
			if (menuPosition < programCount - 1) {
				menuPosition++;
			}
			else
			{
				menuPosition = 0;
				view->errorBlink();		
			}
			setMenuItem(menuPosition);		
		}
		else if (buttons & BUTTON_LEFT) {
			if (menuPosition > 0) {
				menuPosition--;
			}
			else
			{
				menuPosition = programCount-1;
				view->errorBlink();
			}
			setMenuItem(menuPosition);
		}
		// UP and DOWN changes active programs argument
		else if (buttons & BUTTON_UP) {
			if (programArg < argMax)
			{
				programArg++;
				setArgument(programArg);
			}
			else
				view->errorBlink();	
		}
		else if (buttons & BUTTON_DOWN) {		
			if (programArg > argMin)
			{
				programArg--;
				setArgument(programArg);
			}
			else
				view->errorBlink();	
		}
		// Select activate new program or changes mode on existing one
		else if (buttons & BUTTON_SELECT) {
			if (menuPosition == activeProgram)
				changeMode();
			else
				setProgram(menuPosition);	
		}		 

		// This is to enforce "key press" instead of "key down" event
		buttonsPressed = true;
	 }	
	else if (!buttons)
	{
		buttonsPressed = false;
	}
}

/**
 Makes given program active

 @param		program		index of the program to be set active
*/
void Controller::setProgram(byte program)
{
	// change program and set default argument
	activeProgram = program;		
	programArg  = 0;
	// Cancel IDLE mode if exists
	state = STATE_RUNNING;

	// get min and max args for input sanity check
	argMax = programs[activeProgram]->getArgumentMax();
	argMin = programs[activeProgram]->getArgumentMin();
	programs[activeProgram]->init();

	// Display program name on the screen
	char name[LABEL_LENGTH];
	programs[activeProgram]->getName(name);
	setArgument(programArg);
	view->setProgram(name);	
}

/**
 Change mode of the active program

 Roates through the mode if the program is capable of it
*/
void Controller::changeMode()
{
	activeMode++;
	if (activeMode >= programs[activeProgram]->getModeCount())
	{
		activeMode = 0;
	}

	programs[activeProgram]->setMode(activeMode);
}

/**
 Display given program name as a menut item

 @param		index	program index
*/
void Controller::setMenuItem(byte index)
{	
	char name[LABEL_LENGTH];
	programs[index]->getName(name);
	view->setMenuItem(name);
}

/**
 Set argument for active program

 @param		arg		argument value
*/
void Controller::setArgument(int arg)
{	
	// set the argument
	programArg = arg;
	programs[activeProgram]->setArgument(arg);

	// Get human textual meaning for argument and dislay it
	char name[LABEL_LENGTH];
	programs[activeProgram]->getArgumentText(name);
	view->setArgument(name);
}
