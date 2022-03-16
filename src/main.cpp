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


  // Debugging
  num_sec = 0;
  pinMode(ledPin, OUTPUT);
  pinMode(cyclePin, INPUT);
}

void loop(){
  if (cycle){ // Cycle has been pressed, PCINT fired
    cycle = false;
    layouts.cycle();
  }

  if (num_sec >= 15){ // If no key has been pressed for >5s
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
      Serial.print(key);
      Serial.print(" | ");
      Serial.print(layouts.layout_idx);
      Serial.print(" | ");
      Serial.println(layouts.names[layouts.layout_idx]);

      num_sec = 0;
      layouts.funcArr[layouts.layout_idx](key);
    }
  }
}