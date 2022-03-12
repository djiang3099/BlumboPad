#include <Arduino.h>
// #include <Keypad.h>
// #include <HID-Project.h>
#include "sleep.h"

void setup(){
  Serial.begin(9600);
  disableModules();
  setupPCInt();
  setupTimer1Int();
  setupKeypad();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  delay(50);
  // Partition into sleeping and awake
  if (num_sec >= 5 && num_keys >= 4){
    if (awake){
      Serial.println("Go to sleep");
      // Simulate sleeping, do nothing
      awake = false;

      // Setup the keypad to wait for any keypress
      sleepKeypadPins();
      enablePCInt();

      goToSleep();
      initialiseKeypadPins();
      // detachUSB();
    }
  }
  else{
    // Simulate awake
    if (!awake){
      // Just woken up, reset states 
      Serial.println("Waking up");
      num_sec = 0;
      num_keys = 0;
      awake = true;
      // USBDevice.attach();
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
        num_keys++;
        Serial.println(key);
      }
    }
  }
}