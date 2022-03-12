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

extern const int ledPin;
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

ISR(PCINT0_vect);
ISR(TIMER1_COMPA_vect);

#endif