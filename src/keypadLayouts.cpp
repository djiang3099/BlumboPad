// This file will handle all keypad related functions 
// Initiate
// Cycle through states/keypad layouts
// Import layouts from another file
#include "keypadLayouts.h"

// #include <Arduino.h>
// #include <Keypad.h>
// #include <HID-Project.h>

KeypadLayouts::KeypadLayouts(){
  layout_idx = 0;
}

void KeypadLayouts::cycle(){
  layout_idx = (layout_idx + 1) % num_layouts;
  Serial.print("Cycle! | ");
  Serial.println(layout_idx);
  digitalWrite(led0, layout_idx & 0x01);
  digitalWrite(led1, layout_idx >> 1 & 0x01);
}

void key0(char key){
  switch (key) {
    case '1':
      Keyboard.press('7');
      // Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.press('8');
      // Keyboard.releaseAll();
      break;
    case '3':
      Keyboard.press('9');
      // Keyboard.releaseAll();
      break;
    case '4':
      Keyboard.press('4');
      // Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.press('5');
      // Keyboard.releaseAll();
      break;
    case '6':
      Keyboard.press('6');
      // Keyboard.releaseAll();
      break;
    case '7':
      Keyboard.press('1');
      // Keyboard.releaseAll();
      break;
    case '8':
      Keyboard.press('2');
      // Keyboard.releaseAll();
      break;
    case '9':
      Keyboard.press('3');
      // Keyboard.releaseAll();
      break;
    case '0':
      Keyboard.press('0');
      // Keyboard.releaseAll();
      break;
    case '*':
      Keyboard.press('.');
      // Keyboard.releaseAll();
      break;
    case '#':
      Keyboard.press(KEY_RETURN);
      // Keyboard.releaseAll();
      break;
    case 'a':
      Keyboard.press('+');
      // Keyboard.releaseAll();
      break;
    case 'b':
      Keyboard.press('-');
      // Keyboard.releaseAll();
      break;
    case 'c':
      Keyboard.press('*');
      // Keyboard.releaseAll();
      break;
    case 'd':
      Keyboard.press('/');
      // Keyboard.releaseAll();
      break;
  }
  Keyboard.releaseAll();
}

void key2(char key){
  switch (key) {
    case '1':
      Keyboard.press('1');
      break;
    case '2':
      Keyboard.press('2');
      break;
    case '3':
      Keyboard.press('3');
      break;
    case '4':
      Keyboard.press('4');
      break;
    case '5':
      Keyboard.press('5');
      break;
    case '6':
      Keyboard.press('6');
      break;
    case '7':
      Keyboard.press('7');
      break;
    case '8':
      Keyboard.press('8');
      break;
    case '9':
      Keyboard.press('9');
      break;
    case '0':
      Keyboard.press('0');
      break;
    case '*':
      Keyboard.press('.');
      break;
    case '#':
      Keyboard.press(KEY_RETURN);
      break;
    case 'a':
      Keyboard.press('+');
      break;
    case 'b':
      Keyboard.press('-');
      break;
    case 'c':
      Keyboard.press('*');
      break;
    case 'd':
      Keyboard.press('/');
      break;
  }
  Keyboard.releaseAll();
}

void key1(char key){
  switch (key) {
    case '1':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      break;
    case '2':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      break;
    case '3':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      break;
    case '4':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      break;
    case '5':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_BACKSPACE);
      break;
    case '6':
      Keyboard.press(KEY_BACKSPACE);
      break;
    case '7':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('y');
      break;
    case '8':
      Keyboard.press(KEY_DELETE);
      break;
    case '9':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_DELETE);
      break;
    case '*':
      Consumer.write(MEDIA_PREVIOUS);
      break;
    case '#':
      Consumer.write(MEDIA_NEXT);
      break;
    case 'a':
      Consumer.write(MEDIA_VOLUME_UP);
      break;
    case 'b':
      Consumer.write(MEDIA_VOLUME_DOWN);
      break;
    case 'c':
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
    case 'd':
      Consumer.write(MEDIA_PLAY_PAUSE);
      break;
  }
  Keyboard.releaseAll();
}