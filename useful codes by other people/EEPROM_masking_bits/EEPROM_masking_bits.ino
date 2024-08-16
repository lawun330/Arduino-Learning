// this sketch is about masking.
// A mask is a sequence of bits used to identify bits of interest.

#include <EEPROM.h>

int bigData = 268;  // this is a integer 16-bit data (2 bytes)
byte littleData;    // this is 8-bit data (a byte)


void setup() {
  littleData = bigData & 0xFF;  // 0xFF stands for 11, 111, 111
  // this selects the lower byte(right 8 bits).
  // using bitwise AND operation between the original bits and the focusing bits is called masking.
  // masking gives us the ability to select the interested bits and do any kind of operation.
  EEPROM.write(0, littleData);  // writing lower byte data into the address '0'.
  littleData = (bigData >> 8);  // This shift the higher byte (left 8 bits) to the right place 8 times.
  // the left 8 bits become right 8 bits and the new left 8 bits are zeros.
  // this selects the higher byte by shifting.
  EE PROM.write(1, littleData);  // writing higher byte data into the address '1'.
  // this process is called "Little Endian ordering".

  Serial.begin(9600);
  Serial.print(bigData);
  Serial.print(" is written in binary 2 bytes and lower 8-bit is ");
  Serial.print(EEPROM.read(0), DEC);
  Serial.print(" and higher 8-bit is ");
  Serial.println(EEPROM.read(1), DEC);
  Serial.println("NOTE that 1 is 2^8=256 which is shifted right 8 times so it becomes 2^0=1");
  Serial.println("268 = 256+12");
}


void loop() {}


/* We are chopping off 16 bits into two 8 bits , higher byte and lower byte.
 * We use "bitwise AND" operation in here and use '&'.
 * Normal "AND" operation uses '&&'.
 * Right shift operation uses '>> (x)' which means shift right to 'x' times.
 * Example-
      [1 1 0 1 0] - original data
      [1 0 0 0 0] - we put 1 when we want to select the bit in that place
      [1 0 0 0 0] - the above two performs bitwise AND operation and we have now selected the interested bits */
