#ifndef IProgram_h
#define IProgram_h

/**
	IProgram is an interface that represents any program (effect) for the Cannon

	Every effect needs to implement this interface in order to be executable
*/
class IProgram
{
 public:
	// Initialization of the program
	virtual void init() = 0;
	// Perform ONE effect step - this method is periodically called every cycle of main program
	virtual void step() = 0;
	// Get number of modes that program suports
	virtual byte getModeCount() = 0;
	// Set active mode for the program
	virtual void setMode(byte mode) = 0;
};

#endif