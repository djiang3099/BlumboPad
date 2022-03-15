#include <Arduino.h>
// #include <Keypad.h>
// #include <HID-Project.h>
#include "keypadLayouts.h"
#include "sleep.h"

KeypadLayouts layouts;

void setup(){
  Serial.begin(9600);
  disableModules();
  setupPCInt();
  setupTimer1Int();
  setupKeypad();

  num_sec = 0;
  
  pinMode(ledPin, OUTPUT);
}

void loop(){
  if (num_sec >= 5){ // If no key has been pressed for >5s
    sleepKeypad();
  }
  else{
    // put your main code here, to run repeatedly:
    char key = keypad.getKey();
    delay(50); // overcome any debounce delays built into the keypad library
    // Serial.print("Looped");

    if (!key){
      Serial.print("No key");
      // sleepKeypadPins();
      // goToSleep();  
    }
    else{
      Serial.print("Got a key | ");
      Serial.println(PCICR);
      num_sec = 0;
      // num_keys++;
      Serial.println(key);
      layouts.funcArr[0](key);
    }
  }
}