#ifndef IProgram_h
#define IProgram_h

/**
	IProgram is an interface that represents any program (effect) for the Tank.

	Every effect needs to implement this interface in order to be executable by
	the Controller class.
*/
class IProgram
{
 public:
	// Initialization of the program
	virtual void init() = 0;
	// Perform ONE effect step - this method is periodically called every cycle of main program
	virtual void step() = 0;
	// Returns name of the program
	virtual void getName(char *programName) = 0;	

	// Returns true if program is dependent on the speed sensor data
	virtual bool isInterruptDriven() = 0;
	// Set argument value for the program
	virtual void setArgument(short argument) = 0;
	// Get textual meaning of the current argument
	virtual void getArgumentText(char *output) = 0;
	// Get minimal argument value that program supports
	virtual int getArgumentMin() = 0;
	// Get maximal argument value that program supports	
	virtual int getArgumentMax() = 0;

	// Get number of modes that program suports
	virtual byte getModeCount() = 0;
	// Set active mode for the program
	virtual void setMode(byte mode) = 0;

	// Returns minimal execution time in miliseconds for FX rotator
	// 0 -> means program is not suitable for FX rotation
	virtual int getRotationPeriod() = 0;
};

#endif