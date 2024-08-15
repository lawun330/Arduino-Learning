/* This script demonstrates the use of a 4x4 keypad. 
The indicator LED will flash everytime an input is given. 
Equivalent character and integer value of each input is displayed. */


#include <Keypad.h>

int indicator_LED = 13;
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(9600);
  pinMode(indicator_LED, OUTPUT);
}


void loop() {
  digitalWrite(indicator_LED, 0);

  char customKey = customKeypad.getKey();  // input
  if (customKey) {
    digitalWrite(indicator_LED, 1);  // flash LED
    char a = customKey;              // equivalent character
    int n = customKey;               // equivalent integer
    Serial.print(customKey);
    Serial.print(" is equal to character: ");
    Serial.print(a);
    Serial.print(" and integer: ");
    Serial.println(n);
    delay(200);
  }
}
