// This file will handle all keypad related functions 
// Initiate
// Cycle through states/keypad layouts
// Import layouts from another file
#include "keypadLayouts.h"

// #include <Arduino.h>
// #include <Keypad.h>
// #include <HID-Project.h>

KeypadLayouts::KeypadLayouts(){
  layout_num = 0;
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

void key1(char key){
  switch (key) {
    case '1':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      Keyboard.releaseAll();
      break;
    case '3':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      Keyboard.releaseAll();
      break;
    case '4':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.releaseAll();
      break;
    case '6':
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.releaseAll();
      break;
    case '7':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('y');
      Keyboard.releaseAll();
      break;
    case '8':
      Keyboard.press(KEY_DELETE);
      Keyboard.releaseAll();
      break;
    case '9':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_DELETE);
      Keyboard.releaseAll();
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
}