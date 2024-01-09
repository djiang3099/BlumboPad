#ifndef _GUARD_OLED_
#define _GUARD_OLED_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Fonts/FreeSansBold9pt7b.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define TITLE_FONT &FreeSansBold9pt7b

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


struct Oled{
  Adafruit_SSD1306* display;
  bool screen_invert;

  Oled();

  // Input should be all capitalised
  // Prints the title for the OLED
  void printTitle(const char*);

  // Adds a new key function in a 4x4 matrix sequentially
  void addKey(const char*);

  void update();
  
  bool preventScreenBurn();
} ;

#endif