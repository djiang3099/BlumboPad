#include <Arduino.h>
#include "sleep.h"
#include "blumbo_keypad.cpp"

/* ***************************************
   CONFIGURE BELOW FOR THE SPECIFIC KEYPAD 
   *************************************** */
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
byte rowPins[ROWS] = {14, 15, 18, 19}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
char keys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'a', 'b', 'c', 'd'}
};
/* ***************************************
   CONFIGURE ABOVE FOR THE SPECIFIC KEYPAD 
   *************************************** */

const int ledPin = 10;
boolean toggle0 = 0;
int counter = 0;
int num_sec = 0;

int pc_led_pin = 9;

// TESTING STUFF
int num_keys = 0;
boolean awake = true;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setupKeypad(){
  Keyboard.begin();
}

void detachUSB(){
  // disable the USB
  USBCON |= _BV(FRZCLK);  //freeze USB clock
  PLLCSR &= ~_BV(PLLE);   // turn off USB PLL
  USBCON &= ~_BV(USBE);   // disable USB
}

void setupPCInt(){
  pinMode(pc_led_pin, OUTPUT);
  digitalWrite(pc_led_pin, LOW);

  PCMSK0 |= _BV(PCINT1);   // pin 4
  PCMSK0 |= _BV(PCINT3);   // pin 5
 
  PCICR |= (1 << PCIE0);  // Disable PCINT
  PCIFR  |= _BV(PCIF0);   // clear any outstanding interrupts
}

void enablePCInt(){
  digitalWrite(pc_led_pin, HIGH);
  Serial.print("Enable PCINT: ");
  PCIFR  |= _BV(PCIF0);   // clear any outstanding interrupts
  PCICR = 1;   // enable pin change interrupts
  Serial.println(PCICR, BIN);
}

void disablePCInt(){
  digitalWrite(pc_led_pin, LOW);
  Serial.print("Disable PCINT: ");
  PCICR = 0;   // disable pin change interrupts
  Serial.println(PCICR, BIN);
}

//set timer1 to interrupt at 2kHz
void setupTimer1Int(){
  cli();  //stop interrupts

  TCCR1A = 0; // set entire TCCR0A register to 0
  TCCR1B = 0; // same for TCCR0B
  TCNT1  = 0; //initialize counter value to 0
  // set compare match register for 2khz increments
  OCR1A = 62;  // = (8*10^6) / (2000*64) - 1 (must be <256)
  // Turn on CTC mode & Set bits for 64 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

void initialiseKeypadPins(){
  Serial.println("Initialise keypad");
  byte i;
  
  // go back to all pins as per the keypad library
  // Set all cols to OUTPUT and HIGH
  for (i = 0; i < NUMITEMS(colPins); i++){
    pinMode(colPins [i], OUTPUT);
    digitalWrite(colPins [i], HIGH); 
  }  // end of for each column 

  // Set all rows to INPUT and HIGH
  for (i = 0; i < NUMITEMS(rowPins); i++){
    pinMode(rowPins[i], INPUT);
    digitalWrite(rowPins [i], HIGH); 
  }   // end of for each row

}  // end of reconfigurePins

void sleepKeypadPins(){
  Serial.print("Sleep keypad | PCINT: ");
  Serial.println(PCICR, BIN);

  byte i;
   
  // set up to detect a keypress
  // Set all columns to LOW and OUTPUT
  for (i = 0; i < NUMITEMS(colPins); i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);   
  } 

  // Set all rows to HIGH and INPUT
  for (i = 0; i < NUMITEMS(rowPins); i++){
    pinMode(rowPins [i], INPUT);
    digitalWrite(rowPins[i], HIGH); 
  }  // end of for each row
    
  // now check no pins pressed (otherwise we wake on a key release)
  for (i = 0; i < NUMITEMS(rowPins); i++){
    if (digitalRead(rowPins[i]) == LOW){
      Serial.println("Wake on release!");
      initialiseKeypadPins();
      return; 
    } // end of a pin pressed
  }  // end of for each row
}

void goToSleep(){  
  // at this point, pressing a key should connect the high in the row to the 
  // to the low in the column and trigger a pin change

  byte old_PRR0 = PRR0; 
  byte old_PRR1 = PRR1;
  // Serial.println(PRR0, BIN);
  // Serial.println(PRR1, BIN);
  // delay(100);  // Delay here so that above print statements work

  // disable ADC to save power
  // byte old_ADCSRA = ADCSRA;
  // ADCSRA = 0;

  // Detach USB
  Serial.flush();
  // delay(100);
  detachUSB();

  // delay(100);
  // Configure sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();

  // PRR0 = 0xFF;  // Turn off clock; TIMERS 0 & 1; SPI; ADC
  PRR0 = 0b10001101;
  PRR1 = 0xFF;  // turn off various modules

  // delay(5000);
  // Actually go to sleep here
  sleep_cpu();  

  // After wakeup code proceeds from here:
  sleep_disable();
  // delay(100);

  // Reinitiate all modules
  PRR0 = old_PRR0;
  PRR1 = old_PRR1;
  // ADCSRA = old_ADCSRA;

  // Reattach the USB, serial monitor doesn't reconect though...
  USBDevice.attach();
  // delay(1000);
  // Serial.begin(9600);
  // while (!Serial){}

  // Serial.println("Woken up!");
}

void sleepKeypad(){
  // Setup the keypad to wait for any keypress
    sleepKeypadPins();
    enablePCInt();

    goToSleep();
    // initialiseKeypadPins();
}

void disableModules(){
  int PRTIM4 = 4;
  PRR0 |= _BV(PRTWI) | _BV(PRSPI) | _BV(PRADC);   // Disable I2C, SPI, ADC
  PRR1 |= _BV(PRTIM3) | _BV(PRTIM4) | _BV(PRUSART1);  // Disable timers 3,4 & USART
  ADCSRA = 0; // Disable ADC
}

// Pin change ISR
ISR(PCINT0_vect){
  // Key has been pressed, wake up the system
  // Does this automatically?
  Serial.print("PCINT! Key pressed | ");
  Serial.println(PCICR);
  num_sec = 0;

  disablePCInt();
}    

ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
  // generates pulse wave of frequency 2kHz/2 = 1kHz 
  // (takes two cycles for full wave- toggle high then toggle low)
  if(counter < 1984){
    counter++;
  }
  else{
    counter = 0;
    num_sec++;

    // For DEBUG
    Serial.print(num_sec);
    Serial.print(" | ");
    Serial.print(num_keys);
    Serial.print(" | ");
    Serial.print(awake);
    Serial.print(" | ");
    Serial.println(PCICR, BIN);
    if (toggle0){
      digitalWrite(ledPin,HIGH);
      toggle0 = 0;
    }
    else{
      digitalWrite(ledPin,LOW);
      toggle0 = 1;
    }
  }
}