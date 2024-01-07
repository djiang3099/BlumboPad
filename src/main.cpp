#include <Arduino.h>

#include "keypadLayouts.h"
#include "sleep.h"
#include "oled.h"

Oled* Blumbo_oled;
KeypadLayouts* layouts;

void setup(){
  Serial.begin(9600);
  
  Blumbo_oled = new Oled;
  layouts = new KeypadLayouts(Blumbo_oled);
  // disableModules();
  // setupPCInt();
  // setupTimer1Int();
  setupKeypad();

  layouts->initOled();
  initialiseEncoder(INIT_ENC1_2);

  // Debugging---
  // num_sec = 0;
  // pinMode(ledPin, OUTPUT);
  // pinMode(cyclePin, INPUT);

  // delay(3000);
  Serial.println("INITIALISED");

}

void loop(){
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  delay(10); // overcome any debounce delays built into the keypad library
  // Serial.print("Looped");

  byte enc_state = readEnc2();
  if (enc_state > 0){
    Serial.println(getEncCounter(2));
    if (enc_state == ENC_CW){
      Serial.println("Vol up");
      layouts->funcArr[layouts->layout_idx](KEY_ENC_CW);
    }
    else if (enc_state == ENC_CCW){
      Serial.println("Vol dn");
      layouts->funcArr[layouts->layout_idx](KEY_ENC_CCW);
    }
  }

  if (key){
    Serial.print("\nGot a key | ");
    Serial.println(key);
    // Serial.print(" | ");
    // Serial.print(layouts.layout_idx);
    // Serial.print(" | ");
    // Serial.println(layouts.names[layouts.layout_idx]);

    if (key == 15){ // Cycle button pressed
      Serial.println("Cycle");
      layouts->cycle();
    }
    else if (key == 20){  // LED button pressed - Using it to cycle encoder speed for now
      Serial.println("Encoder speed change");
      if (getEncoderDebounce() == 50){  // 50 or 150 can be changed but seem like good values.
        updateEncoderDebounce(150);
      }
      else{
        updateEncoderDebounce(50);
      }
    }
    else{
      // Action the requested key stroke / macro - Defined in keyboardLayouts
      layouts->funcArr[layouts->layout_idx](key);
    }
  }
}