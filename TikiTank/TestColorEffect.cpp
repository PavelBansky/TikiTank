#include "TestColorEffect.h"

/**
 Constructor

 @param		programName	name of the program that will appear on the display
 @param		ledStrip	pointer to LED strip controlling class	 
*/
TestColorEffect::TestColorEffect(char programName[], LPD8806 *ledStrip)
{	
	strncpy(name, programName, sizeof(name));
	strip = ledStrip;	

	strcpy(colors[0].name, "Black");	colors[0].color = strip->Color(0, 0, 0);	
	strcpy(colors[1].name, "Red");		colors[1].color = strip->Color(127, 0, 0);	
	strcpy(colors[2].name, "Yellow");	colors[2].color = strip->Color(127, 127, 0);
	strcpy(colors[3].name, "Green");	colors[3].color = strip->Color(0, 127, 0);
	strcpy(colors[4].name, "Aqua");		colors[4].color = strip->Color(0, 127, 127);
	strcpy(colors[5].name, "Blue");		colors[5].color = strip->Color(0, 0, 127);
	strcpy(colors[6].name, "Purple");	colors[6].color = strip->Color(63, 0, 63);
	strcpy(colors[7].name, "Pink");		colors[7].color = strip->Color(127, 10, 73);	
	strcpy(colors[8].name, "White");	colors[8].color = strip->Color(127, 127, 127);	

	argument = 0;
}

void TestColorEffect::init()
{
	for(int j=0; j < strip->numPixels()-1; j++ ) {
		strip->setPixelColor(j, colors[argument].color);
	}
} 

void TestColorEffect::step()
{	
	strip->show();	
	delay(10);
}

void TestColorEffect::setArgument(short arg)
{
	argument = arg;
	// sanity check
	if (argument < 0)
		argument = 0;
	else if (argument >= MAX_SOLID_COLOR_COUNT)
		argument = MAX_SOLID_COLOR_COUNT-1;

	init();
}

void TestColorEffect::getArgumentText(char *output)
{		
	char outstr[LABEL_LENGTH] = "";
	strcat(outstr, colors[argument].name);
	strncpy(output, outstr, sizeof(outstr));		
}

void TestColorEffect::getName(char *programName)
{
	strncpy(programName, name, sizeof(name));	
}
