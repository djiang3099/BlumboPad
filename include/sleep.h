#ifndef SLEEP_GUARD
#define SLEEP_GUARD

#include <Arduino.h>
#include <avr/sleep.h>
#include <Keypad.h>
#include <HID-Project.h>

// number of items in an array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
#define INIT_ENC1 1
#define INIT_ENC2 2
#define INIT_ENC1_2 0
#define ENC_CW 1
#define ENC_CCW 2
#define KEY_ENC_CW 21
#define KEY_ENC_CCW 22

/* ****************************************************
   CONFIGURE KEYPAD FOR THE SPECIFIC KEYPAD IN CPP FILE
   **************************************************** */

extern boolean cycle;
extern uint16_t debounceDelay;

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
void initialiseEncoder(byte);
uint16_t getEncoderDebounce();
void updateEncoderDebounce(uint16_t);
int readEnc1();
int readEnc2();
int getEncCounter(byte);

ISR(PCINT0_vect);
ISR(TIMER1_COMPA_vect);

#endif