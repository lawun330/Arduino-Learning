// EEPROM is a memory like flash, non volatile unlike RAM
// This sketch writes data into the address of the EEPROM memory and read data from it

#include <EEPROM.h>


void setup() {
  int address, data = 9;
  Serial.begin(9600);
  for (address = 0; address < 1024; address++) {
    EEPROM.write(address, data);
  }

  for (address = 0; address < 1024; address++) {
    Serial.println(EEPROM.read(address), DEC);
  }
}

void loop() {}

// read/write one byte (8bits) at a time into the address
// it chops off and ignores the higher bytes, writing only the low least significant byte if more than one byte is given
