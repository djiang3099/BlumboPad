// This file will handle all keypad related functions 
// Initiate
// Cycle through states/keypad layouts
// Import layouts from another file
#include "keypadLayouts.h"

// void copyFunc(char){
//   Keyboard.press(KEY_LEFT_CTRL);
//   Keyboard.press('c');
// }

KeyFunc::KeyFunc(char* Name, keyActFunc Func){
  name = Name;
  func = Func;
}

KeypadLayouts::KeypadLayouts(Oled* _oled_){
  layout_idx = 0;
  _oled = _oled_;
}

void KeypadLayouts::cycle(){
  layout_idx = (layout_idx + 1) % num_layouts;
  Serial.print("Cycle! | ");
  Serial.println(layout_idx);
  digitalWrite(led0, layout_idx & 0x01);
  (this->*displayArr[layout_idx])();
}

void KeypadLayouts::initOled(){
  _oled->printTitle(names[layout_idx]);
  (this->*displayArr[layout_idx])();
}

void KeypadLayouts::sleepOled(){
  _oled->display->clearDisplay();
  _oled->display->display();
}

void key0(char key){
  switch (key) {
    case '00':
      Keyboard.press('7');
      break;
    case '01':
      Keyboard.press('8');
      break;
    case '02':
      Keyboard.press('9');
      break;
    case '03':
      Keyboard.press('+');
      break;
    case '04':
      Keyboard.press('A');
      break;
    case '10':
      Keyboard.press('4');
      break;
    case '11':
      Keyboard.press('5');
      break;
    case '12':
      Keyboard.press('6');
      break;
    case '13':
      Keyboard.press('-');
      break;
    case '14':
      Keyboard.press('B');
      break;
    case '20':
      Keyboard.press('1');
      break;
    case '21':
      Keyboard.press('2');
      break;
    case '22':
      Keyboard.press('3');
      break;
    case '23':
      Keyboard.press('*');
      break;
    case '24':
      Keyboard.press('C');
      break;
    case '30':
      Keyboard.press('0');
      break;
    case '31':
      Keyboard.press('.');
      break;
    case '32':
      Keyboard.press('/');
      break;
    case '33':
      Keyboard.press(KEY_RETURN);
      break;
    case '34':
      Keyboard.press('D');
      break;
  }
  Keyboard.releaseAll();
}

void KeypadLayouts::display0(){
  _oled->printTitle("Key0");
  _oled->addKey("7");
  _oled->addKey("8");
  _oled->addKey("9");
  _oled->addKey("A");
  _oled->addKey("4");
  _oled->addKey("5");
  _oled->addKey("6");
  _oled->addKey("B");
  _oled->addKey("1");
  _oled->addKey("2");
  _oled->addKey("3");
  _oled->addKey("C");
  _oled->addKey("*");
  _oled->addKey("0");
  _oled->addKey("#");
  _oled->addKey("D");
  _oled->update();
}

void KeypadLayouts::display1(){
  _oled->printTitle("Key1");
  _oled->addKey("1");
  _oled->addKey("2");
  _oled->addKey("3");
  _oled->addKey("A");
  _oled->addKey("4");
  _oled->addKey("5");
  _oled->addKey("6");
  _oled->addKey("B");
  _oled->addKey("7");
  _oled->addKey("8");
  _oled->addKey("9");
  _oled->addKey("C");
  _oled->addKey("*");
  _oled->addKey("0");
  _oled->addKey("#");
  _oled->addKey("D");
  _oled->update();
}

void KeypadLayouts::display2(){
  _oled->printTitle("Key0 Again");
  _oled->addKey("7");
  _oled->addKey("8");
  _oled->addKey("9");
  _oled->addKey("A");
  _oled->addKey("4");
  _oled->addKey("5");
  _oled->addKey("6");
  _oled->addKey("B");
  _oled->addKey("1");
  _oled->addKey("2");
  _oled->addKey("3");
  _oled->addKey("C");
  _oled->addKey("*");
  _oled->addKey("0");
  _oled->addKey("#");
  _oled->addKey("D");
  _oled->update();
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