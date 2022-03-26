#ifndef _KEYPADLAYOUTGUARD_
#define _KEYPADLAYOUTGUARD_

#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include "oled.h"

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
  static const byte led0 = 8;   // For debugging
  // static const byte led1 = 3;   // For debugging
  uint8_t layout_idx;
  Oled* _oled;
  
  void display0();
  void display1();
  void display2();

  /* ******************************************************
     This needs to be changed when adding/deleting profiles
  ****************************************************** */
  static const uint8_t num_layouts = 3;
  char* names[num_layouts] = {"Calc", "Win", "Mac"};
  layoutFunc funcArr[num_layouts] = {key0, key2, key0};
  displayFunc displayArr[num_layouts] = {&KeypadLayouts::display0, &KeypadLayouts::display1, &KeypadLayouts::display2};

  // TODO: Add array of key function strings (Copy, cut, Ret)

  KeypadLayouts(Oled*);
  void cycle();

  void initOled();
  void sleepOled();
};

#endif