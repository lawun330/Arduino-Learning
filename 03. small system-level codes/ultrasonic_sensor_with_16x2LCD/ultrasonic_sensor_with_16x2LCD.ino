/* This script combines a 16x2 LCD with an ultrasonic sensor to display distance measurements.
The LCD is controlled directly using digital pins, not via the I2C protocol.
This script can be used for various measurements (e.g., height, depth) and display the results.
Example scenario: measuring how full a recycle bin is. */


#include "LiquidCrystal.h"

// pin definitions
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2, en = 11, rs = 12;  // LCD pins
const int trig = 9;
const int echo = 8;

// Threshold values
const int FULL_THRESHOLD = 10;
const int HALF_FULL_THRESHOLD = 30;

LiquidCrystal my_lcd(rs, en, d4, d5, d6, d7);  // pass LCD pins


void setup() {
  Serial.begin(9600);
  my_lcd.begin(16, 2);  // initialize the LCD (16 columns, 2 rows)

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  my_lcd.print("Distance: ");
  my_lcd.setCursor(14, 0);
  my_lcd.print("cm");
}


void loop() {
  int distance = getDistance();
  Serial.println(distance);

  my_lcd.setCursor(10, 0);  // set the cursor to the 10th column and 0th row
  my_lcd.print(distance);   // print the distance on the LCD

  if (distance < FULL_THRESHOLD) {
    printMessage("Bin is full");
  } else if (distance < HALF_FULL_THRESHOLD) {
    printMessage("Bin is half full");
  } else {
    printMessage("Bin is empty");
  }

  delay(500);  // it is like the refresh rate of the LCD

  my_lcd.setCursor(10, 0);  // set the cursor to the 10th column and 0th row
  my_lcd.print("    ");     // print 4 spaces to clear the previous distance
}


// function to get the distance from the ultrasonic sensor
int getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2;
}


// function to clear and print a message on the second line of the LCD
void printMessage(String message) {
  my_lcd.setCursor(0, 1);
  my_lcd.print("                ");  // Clear the line
  my_lcd.setCursor(0, 1);
  my_lcd.print(message);
}