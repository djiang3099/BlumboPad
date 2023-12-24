#include <Arduino.h>

#include "keypadLayouts.h"
#include "sleep.h"
#include "oled.h"

// void setup(){
//   Serial.begin(9600);
// }

// void loop(){
//   Serial.println("Hello");
//   delay(1000);
// }

Oled* Blumbo_oled;
KeypadLayouts* layouts;

void setup(){
  Serial.begin(9600);
  
  Blumbo_oled = new Oled;
  layouts = new KeypadLayouts(Blumbo_oled);
  disableModules();
  setupPCInt();
  // setupTimer1Int();
  setupKeypad();

  layouts->initOled();

  // Debugging
  num_sec = 0;
  pinMode(ledPin, OUTPUT);
  pinMode(cyclePin, INPUT);
}

void loop(){
  if (cycle){ // Cycle has been pressed, PCINT fired
    delay(50);
    cycle = false;
    layouts->cycle();

  }

  // if (num_sec >= 15){ // If no key has been pressed for >5s
  //   // TODO: Disable the OLED before sleeping 
  //   layouts->sleepOled();

  //   // Put system to sleep
  //   sleepKeypad();

  //   // TODO: Wake up the OLED again
  //   layouts->initOled();
  // }
  else{
    // put your main code here, to run repeatedly:
    char key = keypad.getKey();
    delay(50); // overcome any debounce delays built into the keypad library
    // Serial.print("Looped");

    if (!key){
      // Serial.print("No key");
      // sleepKeypadPins();
      // goToSleep();  
    }
    else{
      Serial.print("Got a key | ");
      Serial.print(key);
      Serial.print(" | ");
      // Serial.print(layouts.layout_idx);
      Serial.print(" | ");
      // Serial.println(layouts.names[layouts.layout_idx]);

      num_sec = 0;
      layouts->funcArr[layouts->layout_idx](key);
    }
  }
}