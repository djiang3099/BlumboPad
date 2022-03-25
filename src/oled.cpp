#include "oled.h"

Oled::Oled(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  if(!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); 
    for(;;); // Don't proceed, loop forever
  }
  display->clearDisplay();
  printTitle("BlumboPad v1");
}

void Oled::printTitle(const char* title){
  display->setCursor(0,7);
  display->setFont(TITLE_FONT);
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(WHITE);

  String str_title = title;
  if (strlen(title) > 13){
    display->println(str_title.substring(0, 12));
  }
  else{
    display->println(title); // Max 11 characters long
  }

  // Reset the font and move the cursor down 
  display->setFont(NULL);
  display->setCursor(0, display->getCursorY() - 11 );

  // Underscore the Title
  display->drawLine(0, display->getCursorY()-2, SCREEN_WIDTH, display->getCursorY()-2, SSD1306_WHITE);

  // display->display();
}

void Oled::addKey(const char* key){
  // This function writes another key onto the OLED. 
  // Then move the cursor across to fill 4 rows.
  // Check if end of row, if so, move cursor to next row.
  display->print(key);

  // 32 pixels per key
  byte curr_col = display->getCursorX()/(SCREEN_WIDTH/4);
  if (curr_col == 3){
    // Need to move to next row 
    display->setCursor(0, display->getCursorY() + 13);
  }
  else{
    // Need to move to next col 
    display->setCursor((curr_col+1) * SCREEN_WIDTH/4, display->getCursorY());
  }
  // display->display();
}

void Oled::update(){
  display->display();
}