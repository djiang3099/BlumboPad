#ifndef _KEYPADLAYOUTGUARD_
#define _KEYPADLAYOUTGUARD_

#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>

typedef void(*layoutFunc)(char);

void key0(char);
void key1(char);

struct KeypadLayouts{
  static const byte led0 = 8;
  static const byte led1 = 9;
  byte layout_num;
  
  /* ******************************************************
     This needs to be changed when adding/deleting profiles
  ****************************************************** */
  static const byte num_layouts = 3;
  String names[num_layouts] = {"Calc", "Win", "Mac"};
  layoutFunc funcArr[num_layouts] = {key0, key1, key0};
  // TODO: Add array of key function strings (Copy, cut, Ret)

  KeypadLayouts();

  // void testFunc();
};

#endif