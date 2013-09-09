/**
* Tiki Tank Speed Sensor 1.0
* http://www.tikitank.com/
* 
* This is the firmware for the speed sensor CPU that reads the HAL sensor values
* 
* Intended CPU: ATMega 328
*
*/

// Pin where the HAL sensor comparator is connected
const int sensorPin = 3;
// Pin for status LED pin
const int ledPin = 7;
// Pin for the analog input (speed coeficient) 
const int potPin = A2;
// Timeout interval in milliseconds
const int timeout = 1300;
// Interval for sending data out to main CPU (milliseconds)
const int sendFrequency = 150;

// Shortest time between pulses (to prevent glitches and bouncing)
const int minimumTickLength = 90;

#define TICK_NONE 0
#define TICK_FIRST 1
#define TICK_REGULAR 2

int coef = 330;
volatile int outputInterval =0;
volatile unsigned long tickTime = 0;
volatile unsigned long watchdog = 0;
unsigned long sendTimer = 0;
volatile byte ticking = TICK_NONE;
volatile short delta = 0;
volatile short lastDelta = 0;
volatile short avg = 0;
volatile short deviation = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
	pinMode(sensorPin, INPUT);
   
	Serial.write((uint8_t)0);
	attachInterrupt(1, interruptHandler, RISING);
}

void loop()
{
	// Reflectt sensot status to LED. This is visual control when adjusting the sensor sensitivity
	digitalWrite(ledPin, digitalRead(sensorPin));

	// Read coeficient value from the analog input 
	coef = map(analogRead(potPin), 0, 1023, 900, 1100);  

	// Timeout check
	if ((millis() - watchdog) > timeout)
	{
		ticking = TICK_NONE;
		outputInterval = 0; //  delta = lastDelta = 0;
	}

	// Send data out every "sendFrequency"
	if ((millis() - sendTimer) > sendFrequency)
	{
		Serial.write((uint8_t)outputInterval);
		sendTimer = millis();
	}
}

void interruptHandler()
{
	// First pulse => start measuring the time
	if (ticking == TICK_NONE)
	{
		tickTime = watchdog = millis();
		ticking = TICK_FIRST;
	}
	// every other pulse do the measurement
	else
	{		
		delta = millis() - tickTime;

		// if it's a first tick make a new last delta
		lastDelta = (lastDelta == 0) ? delta : lastDelta;
		avg = (delta+lastDelta)/2;
		deviation = delta * 0.25;		
		
		// Interval must have a minimum length 
		if (delta > minimumTickLength)
		{
			// Interval must be reasonably close to the previous interval
			if (abs(delta-avg) <= deviation || ticking == TICK_FIRST)

			tickTime = watchdog = millis();
			lastDelta = delta;

			// This speed calculation formula is based on distance between LEDs on the strip
			outputInterval = ((float)delta / (float)coef) * 60;

			ticking = TICK_REGULAR;
		}
	}
}
