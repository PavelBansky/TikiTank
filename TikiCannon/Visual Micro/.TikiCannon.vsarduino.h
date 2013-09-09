#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Uno
#define __AVR_ATmega328P__
#define ARDUINO 105
#define __AVR__
#define F_CPU 16000000L
#define __cplusplus
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__
#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define prog_void
#define PGM_VOID_P int
#define NOINLINE __attribute__((noinline))

typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void setProgram(byte program);
uint8_t readButtons();
void changeProgram();
void changeMode();

#include "c:\Program Files (x86)\arduino-1.0.5\hardware\arduino\variants\standard\pins_arduino.h" 
#include "c:\Program Files (x86)\arduino-1.0.5\hardware\arduino\cores\arduino\arduino.h"
#include "D:\Home\Documents\Arduino\TikiCannon\TikiCannon.ino"
#include "D:\Home\Documents\Arduino\TikiCannon\CannonBallEffect.cpp"
#include "D:\Home\Documents\Arduino\TikiCannon\CannonBallEffect.h"
#include "D:\Home\Documents\Arduino\TikiCannon\Constants.h"
#include "D:\Home\Documents\Arduino\TikiCannon\IProgram.h"
#include "D:\Home\Documents\Arduino\TikiCannon\RainbowEffect.cpp"
#include "D:\Home\Documents\Arduino\TikiCannon\RainbowEffect.h"
#include "D:\Home\Documents\Arduino\TikiCannon\RunningColorEffect.cpp"
#include "D:\Home\Documents\Arduino\TikiCannon\RunningColorEffect.h"
#include "D:\Home\Documents\Arduino\TikiCannon\SolidColorEffect.cpp"
#include "D:\Home\Documents\Arduino\TikiCannon\SolidColorEffect.h"
#include "D:\Home\Documents\Arduino\TikiCannon\TestColorEffect.cpp"
#include "D:\Home\Documents\Arduino\TikiCannon\TestColorEffect.h"
#endif
