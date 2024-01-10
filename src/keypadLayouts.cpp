// This file will handle all keypad related functions 
// Initiate
// Cycle through states/keypad layouts
// Import layouts from another file
#include "../include/keypadLayouts.h"

// void copyFunc(char){
//   Keyboard.press(KEY_LEFT_CTRL);
//   Keyboard.press('c');
// }

// TODO: Allow configurable encoder debounce delays. 

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
  (this->*displayArr[layout_idx])();
}

// void KeypadLayouts::cycleEncoder(){
//   debounce_idx = (debounce_idx + 1) % num_debounce;
//   Serial.print("Cycle Encoder! | ");
//   Serial.println(debounce_idx);
// }

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
    case 1:
      Keyboard.press('7');
      break;
    case 2:
      Keyboard.press('8');
      break;
    case 3:
      Keyboard.press('9');
      break;
    case 4:
      Keyboard.press('+');
      break;
    // case 5: // ENCODER SW17 (Upper one)
    //   Keyboard.press(MEDIA_PLAY_PAUSE);
    //   break;
    case 6:
      Keyboard.press('4');
      break;
    case 7:
      Keyboard.press('5');
      break;
    case 8:
      Keyboard.press('6');
      break;
    case 9:
      Keyboard.press('-');
      break;
    case 10: // ENCODER SW18 (Mid / lower one)
      Keyboard.press(KEY_RETURN);
      break;
    case 11:
      Keyboard.press('1');
      break;
    case 12:
      Keyboard.press('2');
      break;
    case 13:
      Keyboard.press('3');
      break;
    case 14:
      Keyboard.press('*');
      break;
    case 15:  // Cycle
      Keyboard.press('C');
      break;
    case 16:
      Keyboard.press('0');
      break;
    case 17:
      Keyboard.press('.');
      break;
    case 18:
      Keyboard.press('/');
      break;
    case 19:
      Keyboard.press(KEY_RETURN);
      break;
    case 20:  // LED
      Keyboard.press('D');
      break;
    case KEY_ENC_CW:  // Scroll vertically right
      Keyboard.press(KEY_LEFT_SHIFT); 
      Mouse.move(0,0,-5); // 5 seems like a reasonable number...
      break;
    case KEY_ENC_CCW: // Scroll vertically left
      Keyboard.press(KEY_LEFT_SHIFT);
      Mouse.move(0,0,5);
      break;
  }
  Keyboard.releaseAll();
}

void KeypadLayouts::display0(){
  _oled->printTitle("Calc");
  _oled->addKey("7");
  _oled->addKey("8");
  _oled->addKey("9");
  _oled->addKey("+");
  _oled->addKey("4");
  _oled->addKey("5");
  _oled->addKey("6");
  _oled->addKey("-");
  _oled->addKey("1");
  _oled->addKey("2");
  _oled->addKey("3");
  _oled->addKey("*");
  _oled->addKey("0");
  _oled->addKey(".");
  _oled->addKey(",");
  _oled->addKey("RET");
  _oled->update();
}

void key1(char key){
  switch (key) {
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      break;
    case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      break;
    case 3:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      break;
    case 4:
      Keyboard.press(KEY_BACKSPACE);
      break;
    // case 5: // ENCODER SW17 (Upper one)
    //   Keyboard.press(MEDIA_PLAY_PAUSE);
    //   break;
    case 6:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      break;
    case 7:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('y');
      break;
    case 8:
      Keyboard.press(KEY_UP_ARROW);
      break;
    case 9:
      Keyboard.press(KEY_DELETE);
      break;
    case 10: // ENCODER SW18 (Mid / lower one)
      Consumer.write(MEDIA_PLAY_PAUSE);
      break;
    case 11:
      Keyboard.press(KEY_SPACE);
      break;
    case 12:
      Keyboard.press(KEY_LEFT_ARROW);
      break;
    case 13:
      Keyboard.press(KEY_DOWN_ARROW);
      break;
    case 14:
      Keyboard.press(KEY_RIGHT_ARROW);
      break;
    case 15:  // Cycle
      Keyboard.press('C');
      break;
    case 16:
      Consumer.write(MEDIA_PREVIOUS);
      break;
    case 17:
      Consumer.write(MEDIA_NEXT);
      break;
    case 18:
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
    case 19:
      Keyboard.press(KEY_RETURN);
      break;
    case 20:  // LED
      Keyboard.press('D');
      break;
    case KEY_ENC_CW:
      Consumer.write(MEDIA_VOL_UP);
      break;
    case KEY_ENC_CCW:
      Consumer.write(MEDIA_VOL_DOWN);
      break;
  }
  Keyboard.releaseAll();
}

void KeypadLayouts::display1(){
  _oled->printTitle("Macro1");
  _oled->addKey("C-C");
  _oled->addKey("C-V");
  _oled->addKey("C-X");
  _oled->addKey("Back");
  _oled->addKey("C-Z");
  _oled->addKey("C-Y");
  _oled->addKey("UP");
  _oled->addKey("Del");
  _oled->addKey("Space");
  _oled->addKey("LEFT");
  _oled->addKey("DOWN");
  _oled->addKey("RGT");
  _oled->addKey("Prev");
  _oled->addKey("Next");
  _oled->addKey("Mute");
  _oled->addKey("RET");
  _oled->update();
}