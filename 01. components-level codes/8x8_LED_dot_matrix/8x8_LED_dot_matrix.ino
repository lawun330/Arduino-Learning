/* This script illustrates the use of 8x8 LED dot matrix display. 
A total of 16 pins is used without any additional modules (display driver, etc.). */


// row pins
#define row1 6
#define row2 3
#define row3 8
#define row4 2
#define row5 10
#define row6 9
#define row7 A2
#define row8 13

// column pins
#define col1 A4
#define col2 A3
#define col3 11
#define col4 7
#define col5 12
#define col6 5
#define col7 4
#define col8 A0

const byte rows[] = { row1, row2, row3, row4, row5, row6, row7, row8 };

// create a custom pattern # 0 -> light off # 1 -> light on
byte custom_pattern[] = { B11110010,
                          B00010010,
                          B00010010,
                          B11111110,
                          B10010000,
                          B10010000,
                          B10011110,
                          B00000000 };


void setup() {
  for (int d = 2; d < 14; d++) { pinMode(d, OUTPUT); }  // all digital pins
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}


void loop() {
  light(custom_pattern);
}


// function to set the column
void column(byte b) {
  digitalWrite(col1, (~b >> 0) & 0x01);
  digitalWrite(col2, (~b >> 1) & 0x01);
  digitalWrite(col3, (~b >> 2) & 0x01);
  digitalWrite(col4, (~b >> 3) & 0x01);
  digitalWrite(col5, (~b >> 4) & 0x01);
  digitalWrite(col6, (~b >> 5) & 0x01);
  digitalWrite(col7, (~b >> 6) & 0x01);
  digitalWrite(col8, (~b >> 7) & 0x01);
}


// function to light the LED dot matrix
void light(byte pattern[]) {
  for (byte i = 0; i < 8; i++) {
    column(pattern[i]);
    digitalWrite(rows[i], HIGH);
    delay(2);
    digitalWrite(rows[i], LOW);
  }
}
