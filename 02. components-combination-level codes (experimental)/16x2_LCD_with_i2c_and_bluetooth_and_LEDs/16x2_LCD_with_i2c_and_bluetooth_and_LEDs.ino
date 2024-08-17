/* This scripts combines the use of 16x2 LCD (with i2c), bluetooth module and a set of LEDs. 
The bluetooth data is displayed on the LCD and the LEDs are controlled by it. 
It has three modes: 
 - Mode 1: The LEDs are turned on and off in a sequence 1.
 - Mode 2: The LEDs are turned on and off in a sequence 2.
 - Mode 3: All LEDs are turned off. */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(3, 2);      // pass the bluetooth RX and TX pins
LiquidCrystal_I2C my_lcd(0x27, 16, 2);  // pass LCD address, number of columns and number of rows

int pin;

int BL = 13;
int RL = 12;
int GL = 11;
int Y = 10;
int BR = 9;
int RR = 8;
int GR = 7;


void setup() {
  Serial.begin(9600);        // initialize serial communication
  my_bluetooth.begin(9600);  // initialize bluetooth communication

  for (pin = 7; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
  }

  // display welcome message on the LCD
  my_lcd.init();
  my_lcd.backlight();
  my_lcd.print("Welcome!");
  delay(2000);

  // display waiting message on the LCD
  my_lcd.clear();
  my_lcd.print("Waiting for");
  my_lcd.setCursor(0, 1);
  my_lcd.print("commands, Sir");
  delay(2000);
}


void loop() {
  if (my_bluetooth.available()) {
    char ch = my_bluetooth.read();
    my_lcd.clear();  // clear the LCD

    // MODE 1
    if (ch == '1') {
      my_lcd.home();           // move the cursor to the beginning of the first line
      my_lcd.print("Mode 1");  // display the text "Mode 1" on the first line

      // perform LEDs pattern 1
      for (pin = 7; pin <= 13; pin++) {
        digitalWrite(pin, HIGH);
        delay(50);
        digitalWrite(pin, LOW);
      }
      for (pin = 13; pin >= 7; pin--) {
        digitalWrite(pin, HIGH);
        delay(50);
        digitalWrite(pin, LOW);
      }
    }

    // MODE 2
    else if (ch == '2') {
      my_lcd.home();           // move the cursor to the beginning of the first line
      my_lcd.print("Mode 2");  // display the text "Mode 2" on the first line

      // perform LEDs pattern 2
      for (pin = 7; pin <= 9; pin++) {
        digitalWrite(pin, HIGH);
        digitalWrite(20 - pin, HIGH);
        delay(50);
      }
      digitalWrite(Y, HIGH);
      delay(50);
      digitalWrite(Y, LOW);
      delay(50);
      for (pin = 9; pin >= 7; pin--) {
        digitalWrite(pin, LOW);
        digitalWrite(20 - pin, LOW);
        delay(50);
      }
    }

    // MODE 3
    else if (ch == 'S') {
      for (pin = 7; pin <= 13; pin++) {
        digitalWrite(pin, 0);
      }
    }
  }
}
