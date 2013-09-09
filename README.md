Tiki Tank
=========

Source repository for [Tiki Tank](http://www.tikitank.com) mutant vehicle and related software projects

What the hell is Tiki Tank?
---------------------------

Tiki Tank is *mutant vehicle* created as a technological art piece, that demonstrates symbiosis of mechanical, electrotechnical and computer engineering blended with unique design into a DIY masterpiece.

Ok, cut the crap! It is an art car for Burning Man, that's it....


What's inside?
--------------

The repository contains three Arduino projects written in C++. Each project can be opened and compiled in Arduino IDE. However, Visual Studio 2012 with [Arduino extensions](http://www.visualmicro.com/) is recommended as a best way to edit and compile the source code. 

**TikiTank** is firmware for Teensy++ 2.0 unit that controls the tank tread effects

**TikiCannon** is firmware for ATmega328 that controls the tank cannon effect

**TikiSpeesSensor** is firmware for ATmega328 that controls the HAL sensor and sends speed information to the main unit


### Dependencies ###

- Arduino >= 1.00
- [LPD8806 LED strip library for Tiki Tank](https://github.com/pbansky/LPD8806)
- [Adafruit RGB LCD Shield Library](Adafruit-RGB-LCD-Shield-Library)
- [Teensyduino add-in for arduino](https://www.pjrc.com/teensy/teensyduino.html)


Hardware
--------

The whole project requires two Arduino Uno (ATmega328/ATmega168) and one Teensy++ 2.0


More information
----------------

For more information visit [http://www.tikitank.com](http://www.tikitank.com)
