#include <Arduino.h>
#include "oled.h"

oled Blumbo_oled;
void setup(){
  Serial.begin(9600);
  
  // Show initial display buffer contents on the screen 
  // the library initializes this with an Adafruit splash screen.

  Blumbo_oled.printTitle("1445424844344444");

  Blumbo_oled.addKey("pays");
  Blumbo_oled.addKey("this");
  Blumbo_oled.addKey("one3");
  Blumbo_oled.addKey("pota");
  Blumbo_oled.addKey("ctrl");
  Blumbo_oled.addKey("one");
  Blumbo_oled.addKey("on5e");
  Blumbo_oled.addKey("what");
  Blumbo_oled.addKey("o7ne");
  Blumbo_oled.addKey("one");
  Blumbo_oled.addKey("on8e");
  Blumbo_oled.addKey("on5e");
  Blumbo_oled.addKey("o6ne");
  Blumbo_oled.addKey("o7ne");
  Blumbo_oled.addKey("one");
  Blumbo_oled.addKey("on8e");
  Blumbo_oled.update();
  
}

void loop(){
}