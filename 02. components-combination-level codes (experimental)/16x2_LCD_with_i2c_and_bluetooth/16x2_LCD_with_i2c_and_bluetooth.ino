/* This script demonstrates the serial-my_bluetooth communication using LCD. 
Data sent from the phone to the Arduino board is displayed on the LCD. 
Data sent from the Arduino board to the phone is displayed on the phone. 
LCD is connected to the Arduino board using I2C, reducing the number of pins used. 
Pins A4 and A5 are used to connect SDA and SCL to the LCD. 
The backlight is turned on and off using the backlight() and noBacklight() functions. 
The cursor character is turned on and off using the cursor() and noCursor() functions. */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(3, 2);      // pass the bluetooth pins
LiquidCrystal_I2C my_lcd(0x27, 16, 2);  // pass the LCD pins

// custom character for LCD
byte square_character[8] = {  // a block of pixels where 1 refers to dark
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};


void setup() {
  Serial.begin(9600);        // initialize serial communication
  my_bluetooth.begin(9600);  // initialize bluetooth communication

  my_lcd.init();
  my_lcd.backlight();  // turn on the backlight

  displayWelcome();
}


void loop() {
  // data from phone to arduino
  if (my_bluetooth.available()) {  // if bluetooth data is available
    char ch_phone = my_bluetooth.read();
    Serial.print(ch_phone);  // display bluetooth data in serial monitor

    // display bluetooth data in LCD
    for (int row = 0; row < 2; row++) {              // for each row
      for (int column = 0; column < 16; column++) {  // write data in each column
        my_lcd.setCursor(column, row);
        my_lcd.write(ch_phone);  // display those in LCD
      }
    }
    delay(2000);  // give time to read
    refreshLCD();
  }

  // data from arduino to phone
  if (Serial.available()) {  // if serial data is available
    char ch_arduino = Serial.read();
    Serial.print(ch_arduino);        // display serial data in serial monitor
    my_bluetooth.write(ch_arduino);  // display serial data in the phone's app
  }
}


// function to display a welcome message
void displayWelcome() {
  my_lcd.createChar(1, square_character);  // create a custom character // assign it to the code 1
  my_lcd.home();                           // move the cursor to the beginning of the screen
  my_lcd.print("Loading");

  int row = 1;  // set the cursor row position to 1

  for (int column = 0; column < 16; column++) {  // display a line of dashes in an instance since no delay
    my_lcd.setCursor(column, row);               // row 1, col [i]
    my_lcd.print("-");                           // a dash per iteration
  }

  for (int column = 0; column < 16; column++) {  // display a loading screen with one block at a time
    my_lcd.setCursor(column, row);               // row 1, col [i]
    my_lcd.write(byte(1));                       // a block per iteration // 1 is the custom character
    delay(100);                                  // one block at a time with delay
  }

  delay(200);  // wait a bit

  my_lcd.clear();             // clear the screen
  my_lcd.print("Read here");  // display intro

  my_lcd.cursor();  // turn on the cursor character

  delay(2000);  // give time to read
  refreshLCD();
}


// function to refresh the LCD
void refreshLCD() {
  my_lcd.clear();        // clear the screen
  my_lcd.noBacklight();  // turn off the backlight
  delay(500);            // wait a bit for the light action to complete
  my_lcd.backlight();    // turn on the backlight
}
