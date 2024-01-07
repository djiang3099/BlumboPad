#include <Arduino.h>
#include "sleep.h"
#include "keypadLayouts.h"

/* ***************************************
   CONFIGURE BELOW FOR THE SPECIFIC KEYPAD 
   *************************************** */
const byte ENC1A = 20;  // Encoder 1 (SW17, Top)
const byte ENC1B = 21;  // Encoder 1 (SW17)
const byte ENC2A =  8;  // Encoder 2 (SW18, Mid, Right)
const byte ENC2B =  9;  // Encoder 2 (SW18, Mid, Right)
int ENC1_state;
int ENC2_state;
int ENC1_state_last;
int ENC2_state_last;
int ENC1_counter;
int ENC2_counter;
uint16_t debounceDelay;
unsigned long ENC1_lastDebounceTime = 0;
unsigned long ENC2_lastDebounceTime = 0;

const byte ROWS = 4; //four rows
const byte COLS = 5; //three columns
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {19, 18, 15, 14, 16}; //connect to the column pinouts of the keypad
char keys[ROWS][COLS] = {
  { 1,  2,  3,  4,  5},   // 5 = SW17 Encoder
  { 6,  7,  8,  9, 10},   // 10 = SW18 Encoder
  {11, 12, 13, 19, 15},   // 14 and 19 swapped because V1 PCB had an error
  {16, 17, 18, 14, 20}    // 15 = Cycle, 20 = LED
};
/* ***************************************
   CONFIGURE ABOVE FOR THE SPECIFIC KEYPAD 
   *************************************** */

boolean cycle = false;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setupKeypad(){
  Keyboard.begin();
  Consumer.begin();
  Mouse.begin();
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

void initialiseEncoder(byte enc){
  Serial.println("Initialise encoder");
  debounceDelay = 50;
  if (enc == INIT_ENC1_2 || enc == INIT_ENC1){
    pinMode(ENC1A, INPUT_PULLUP);
    pinMode(ENC1B, INPUT_PULLUP);
    ENC1_state_last = digitalRead(ENC1A);
    ENC1_counter = 0;
  }
  if (enc == INIT_ENC1_2 || enc == INIT_ENC2){
    pinMode(ENC2A, INPUT_PULLUP);
    pinMode(ENC2B, INPUT_PULLUP);
    ENC2_state_last = digitalRead(ENC2A);
    ENC2_counter = 0;
  }   
}

uint16_t getEncoderDebounce(){
  return debounceDelay;
}

void updateEncoderDebounce(uint16_t new_delay){
  debounceDelay = new_delay;
}

int readEnc1(){
  int MSB = digitalRead(ENC1A); 
  int LSB = digitalRead(ENC1B); 
  int output = 0; // 0 is no change, 1 is CW, 2 is CCW

  ENC1_state = (MSB << 1) | LSB;

  if (ENC1_state != ENC1_state_last) {
    if (millis() - ENC1_lastDebounceTime > debounceDelay) {
      if ((ENC1_state_last == 0b00 && ENC1_state == 0b01) ||
        (ENC1_state_last == 0b01 && ENC1_state == 0b11) ||
        (ENC1_state_last == 0b11 && ENC1_state == 0b10) ||
        (ENC1_state_last == 0b10 && ENC1_state == 0b00)) {
        ENC2_counter++;
        Serial.print("Counter Clockwise - ");
        Serial.print("ENC1_counter: " + String(ENC1_counter));
        output = ENC_CCW;
      } 
      else if ((ENC1_state_last == 0b00 && ENC1_state == 0b10) ||
              (ENC1_state_last == 0b10 && ENC1_state == 0b11) ||
              (ENC1_state_last == 0b11 && ENC1_state == 0b01) ||
              (ENC1_state_last == 0b01 && ENC1_state == 0b00)) {
        ENC1_counter--;
        Serial.print("Clockwise - ");
        Serial.print("ENC1_counter: " + String(ENC1_counter));
        output = ENC_CW;
      }
      Serial.print(" | Current State: " + String(ENC1_state));
      Serial.println(" | Previous State: " + String(ENC1_state_last));
      ENC1_lastDebounceTime = millis();
      ENC1_state_last = ENC1_state;
      return output;
    }
  }
  ENC1_state_last = ENC1_state;
  return 0;
}

int readEnc2(){
  int MSB = digitalRead(ENC2A); 
  int LSB = digitalRead(ENC2B); 
  int output = 0; // 0 is no change, 1 is CW, 2 is CCW

  ENC2_state = (MSB << 1) | LSB;

  if (ENC2_state != ENC2_state_last) {
    if (millis() - ENC2_lastDebounceTime > debounceDelay) {
      if ((ENC2_state_last == 0b00 && ENC2_state == 0b01) ||
        (ENC2_state_last == 0b01 && ENC2_state == 0b11) ||
        (ENC2_state_last == 0b11 && ENC2_state == 0b10) ||
        (ENC2_state_last == 0b10 && ENC2_state == 0b00)) {
        ENC2_counter++;
        Serial.print("Counter Clockwise - ");
        Serial.print("ENC2_counter: " + String(ENC1_counter));
        output = ENC_CCW;
      } 
      else if ((ENC2_state_last == 0b00 && ENC2_state == 0b10) ||
              (ENC2_state_last == 0b10 && ENC2_state == 0b11) ||
              (ENC2_state_last == 0b11 && ENC2_state == 0b01) ||
              (ENC2_state_last == 0b01 && ENC2_state == 0b00)) {
        ENC2_counter--;
        Serial.print("Clockwise - ");
        Serial.print("ENC2_counter: " + String(ENC1_counter));
        output = ENC_CW;
      }
      Serial.print(" | Current State: " + String(ENC2_state));
      Serial.println(" | Previous State: " + String(ENC2_state_last));
      ENC2_lastDebounceTime = millis();
      ENC2_state_last = ENC2_state;
      return output;
    }
  }
  ENC2_state_last = ENC2_state;
  return 0;
}

int getEncCounter(byte enc_num){
  if (enc_num == 1){
    return ENC1_counter;
  }
  else if (enc_num == 2){
    return ENC2_counter;
  }
}