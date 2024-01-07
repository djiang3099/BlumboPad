#ifndef _KEYPADLAYOUTGUARD_
#define _KEYPADLAYOUTGUARD_

#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include "oled.h"
#include "sleep.h"

// Function ptr TYPEDEF for KEYPAD ENTRY -> KEY ACTION -> Output
typedef void(*layoutFunc)(char);

// Function ptr TYPEDEF for KEYPAD ENTRY -> KEY ACTION
typedef void(*keyActFunc)(char);

void key0(char);
void key1(char);
void key2(char);

struct KeyFunc{
  // String to show on OLED of what key is
  char* name;
  
  // Function pointer for what the keypress will do
  keyActFunc func;

  KeyFunc(char*, keyActFunc);
};

// static KeyFunc* letter;
// static KeyFunc* copy;
// static KeyFunc* paste;
// static KeyFunc* cut; 
// static KeyFunc* undo;
// static KeyFunc* redo;

struct Profiles{
  // Name of the profile, title to be shown on OLED
  char* name;

  // Matrix of keys, each with a Func_Name and Func
  KeyFunc* keys;

  // Method to interpret the Table row for a key press
  static void readKeys();
};

struct KeypadLayouts{
  // Function ptr TYPEDEF for OLED displays
  typedef void(KeypadLayouts::*displayFunc)();

  uint8_t layout_idx;
  // uint8_t debounce_idx;
  Oled* _oled;
  
  void display0();
  void display1();
  // void display2();

  /* ******************************************************
     This needs to be changed when adding/deleting profiles
  ****************************************************** */
  static const uint8_t num_layouts = 2;
  // static const uint8_t num_debounce = 2;
  char* names[num_layouts] = {"Calc", "Win"};
  // int debounceDelayArr[num_debounce] = {50, 150}; // This can be any number to cycle through
  layoutFunc funcArr[num_layouts] = {key0, key1};
  displayFunc displayArr[num_layouts] = {&KeypadLayouts::display0, &KeypadLayouts::display1};


  // TODO: Add array of key function strings (Copy, cut, Ret)

  KeypadLayouts(Oled*);
  void cycle();
  // void cycleEncoder();

  void initOled();
  void sleepOled();
  // int getDebounceDelay();
};

#endif