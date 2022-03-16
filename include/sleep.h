#ifndef SLEEP_GUARD
#define SLEEP_GUARD

#include <Arduino.h>
#include <avr/sleep.h>
#include <Keypad.h>
#include <HID-Project.h>

// number of items in an array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

/* ****************************************************
   CONFIGURE KEYPAD FOR THE SPECIFIC KEYPAD IN CPP FILE
   **************************************************** */

extern boolean cycle;

extern const byte ledPin;
extern const byte cyclePin;

extern boolean toggle0;
extern int counter;
extern int num_sec;

// TESTING STUFF
extern int num_keys;
extern boolean awake;

extern Keypad keypad;

void setupKeypad();
void detachUSB();
void setupPCInt();
void enablePCInt();
void disablePCInt();
void setupTimer1Int();
void initialiseKeypadPins();
void sleepKeypadPins();
void goToSleep();
void disableModules();
void sleepKeypad();

ISR(PCINT0_vect);
ISR(TIMER1_COMPA_vect);

#endif