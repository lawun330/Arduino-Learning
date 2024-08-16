// EEPROM read/write command from serial monitor

#include <EEPROM.h>

String input = "";
byte ch;  // command is interpreted by byte by byte
int address, data;

void setup() {
  Serial.begin(9600);
  Serial.println("WELCOME TO WRITE/READ EEPROM!");
  Serial.println("Examples- 'read 2.' to read data from address 2");
  Serial.println("        - 'write 0002 53.' to write 53 into address 2");
  Serial.println("REMEMBER to add '.' after the command");
  Serial.println();
}

void loop() {
  if (Serial.available()) {
    ch = Serial.read();
    input += (char)ch;  // add up the command string

    if (ch == '.')  // add '.' as the stop signal
    {
      input.trim();  // remove whitespaces at the end of the input
      Serial.println(input);
      switch (input.charAt(0))  // look at the first character
      {
        case 'r':
          if (input.length() > 4) {
            String address_string = input.substring(4);
            address = address_string.toInt();
          }
          Serial.print("EEPROM data-");
          Serial.println(EEPROM.read(address), DEC);  // read the EEPROM data
          break;
        case 'w':
          if (input.length() > 5) {
            String address_string = input.substring(6, 10);  // the address ranges from 0000-1023 eg.address=2 for 0002
            address = address_string.toInt();
            String data_string = input.substring(11);  // last numbers are data to be written
            data = data_string.toInt();
          }
          EEPROM.write(address, data);
          Serial.print("Successfully written the EEPROM data");
          break;
      }


      input = "";  // reset the input for next command
    }
  }
}

// this works too, easier
void AlternativeFunc() {
  String buffer = "";
  buffer = Serial.readString();
  if (buffer.startsWith("read")) {
    address = buffer.substring(buffer.indexOf(' ') + 1).toInt();
    Serial.print("Data from the address : ");
    Serial.print(address);
    Serial.println();
    Serial.println(EEPROM.read(address));
  } else if (buffer.startsWith("write")) {
    address = buffer.substring(6, 10).toInt();
    dataToWrite = buffer.substring(10).toInt();
    Serial.print("Written ");
    Serial.print(dataToWrite);
    Serial.print(" to the address: ");
    Serial.print(address);
    Serial.println();
    EEPROM.write(address, dataToWrite);
  }
}
