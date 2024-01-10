#include <Arduino.h>

#include "include/keypadLayouts.h"
#include "include/sleep.h"
#include "include/oled.h"

Oled* Blumbo_oled;
KeypadLayouts* layouts;

unsigned long long_loop_time;
unsigned long short_loop_time;
unsigned long loop_time;
unsigned long last_loop;

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
  long_loop_time = 3600000; // 1hr
  short_loop_time = 60000;  // 1min
  loop_time = long_loop_time;
  last_loop = millis();

  Serial.println("INITIALISED");

}

void loop(){
  if (millis() - last_loop > loop_time) {
    last_loop = millis();
    // Invert the screen for a short amount of time
    if (Blumbo_oled->preventScreenBurn()){
      loop_time = long_loop_time;
    }
    else{
      loop_time = short_loop_time;
    }
  }
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