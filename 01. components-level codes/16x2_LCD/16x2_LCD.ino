/* This script demonstrates the basic use of 16x2 liquid crystal display (LCD) without any additional modules like i2c. 
It simply prints strings on the display. */


#include "LiquidCrystal.h"

int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal my_lcd(rs, en, d4, d5, d6, d7);

// custom character for LCD 
// ## a heart shape
byte heart_char[8] = {  // a block of pixels where 1 refers to dark
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

// ## an alternative way to define
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};


void setup() {
  my_lcd.begin(16, 2);
  my_lcd.createChar(1, heart_char); // assign 1 to the custom character
}


void loop() {
  my_lcd.clear();
  my_lcd.print("Hello,how are u?");
  delay(2000);
  
  my_lcd.clear();
  my_lcd.print("Good. Thanks!");
  delay(2000);
  
  for (int column = 0; column < 16; column++){  // fill a row
      my_lcd.setCursor(column, 1);
      my_lcd.write(1);  // 1 refers to the heart character
      delay(200);
  }
  delay(800);
}
