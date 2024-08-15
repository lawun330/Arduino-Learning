/* This script demonstrates the use of two 7-segment displays.
It displays each number every second: from 0 to 'x' and then countdown from 'x' to 0. 
'x' is an arbitrary number which is customizable.
7-segment display pins- top: G, F, ground, A, B 
                        bottom: E, D, ground, C, DP (decimal point) 
In wiring, one ground connection is enough. 
# serial communication is discouraged to avoid interferences since all digital pins are used as outputs. 
# array of function pointers is used to make the code more readable and maintainable. 
# if there is a number 'x', x/10 is the tenth digit and x%10 is the unit digit. */


// define the pin of 7SD1 // tenth digit
int Up1 = 8;      // also known as segment A
int Down1 = 11;   // also known as segment D
int UpL1 = 9;     // also known as segment F
int DownL1 = 12;  // also known as segment E
int UpR1 = 7;     // also known as segment B
int DownR1 = 6;   // also known as segment C
int Mid1 = 10;    // also known as segment G

// define the pin of 7SD2 // unit digit
int Up2 = 4;     // also known as segment A
int Down2 = 2;   // also known as segment D
int UpL2 = 5;    // also known as segment F
int DownL2 = 3;  // also known as segment E
int UpR2 = 1;    // also known as segment B
int DownR2 = 0;  // also known as segment C
int Mid2 = 13;   // also known as segment G

// array of two 7-segment displays for better control
int display[2][7] = {
  { Up1, Down1, UpL1, DownL1, UpR1, DownR1, Mid1 },  // 7SD1 // tenth digit
  { Up2, Down2, UpL2, DownL2, UpR2, DownR2, Mid2 }   // 7SD2 // unit digit
};


void setup() {
  //Serial.begin(9600); // serial communication is discouraged to avoid interferences since all digital pins are used as outputs
  for (int pin = 0; pin < 14; pin++) {  // pins 0 to 13
    pinMode(pin, OUTPUT);
  }
}


void loop() {
  countup(12);    // from 0 to 12
  countdown(20);  // from 20 to 0
}

/********************************************************************************************/

// function to show '0' on display
void zero(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 1);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 0);
}


// function to show '1' on display
void one(int a[]) {
  digitalWrite(a[0], 0);
  digitalWrite(a[1], 0);
  digitalWrite(a[2], 0);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 0);
}


// function to show '2' on display
void two(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 0);
  digitalWrite(a[3], 1);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 0);
  digitalWrite(a[6], 1);
}


// function to show '3' on display
void three(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 0);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to show '4' on display
void four(int a[]) {
  digitalWrite(a[0], 0);
  digitalWrite(a[1], 0);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to show '5' on display
void five(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 0);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to show '6' on display
void six(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 1);
  digitalWrite(a[4], 0);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to show '7' on display
void seven(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 0);
  digitalWrite(a[2], 0);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 0);
}


// function to show '8' on display
void eight(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 1);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to show '9' on display
void nine(int a[]) {
  digitalWrite(a[0], 1);
  digitalWrite(a[1], 1);
  digitalWrite(a[2], 1);
  digitalWrite(a[3], 0);
  digitalWrite(a[4], 1);
  digitalWrite(a[5], 1);
  digitalWrite(a[6], 1);
}


// function to turn off all the 7-segment displays
void Off() {
  for (int pin = 0; pin < 14; pin++) {  // pins 0 to 13
    digitalWrite(pin, 0);
  }
}

/********************************************************************************************/

// array to contain those function pointers for both 7-segment displays
void (*segment[10])(int[]) = { zero, one, two, three, four, five, six, seven, eight, nine };


// function to count up from 0 to 'x'
void countup(int x) {
  int i, j;
  // Example: if x = 23 --> this goes from 00 to 20
  for (i = 0; i < (x / 10); i++) {  // the tenth digit is from 0 to desired value
    for (j = 0; j < 10; j++) {      // the unit digit is from 0 to 9
      segment[i](display[0]);       // display the tenth digit
      segment[j](display[1]);       // display the unit digit
      delay(1000);
      Off();
    }
  }
  // Example: if x = 23 --> this goes from 20 to 23
  if (i == (x / 10)) {                 // the tenth digit is already at desired value
    for (j = 0; j <= (x % 10); j++) {  // the unit digit is from 0 to desired value
      segment[i](display[0]);          // display the tenth digit
      segment[j](display[1]);          // display the unit digit
      delay(1000);
      Off();
    }
  }
}


// function to count down from 'x' to 0
void countdown(int x) {
  for (int i = x; i >= 0; i--) {
    segment[i / 10](display[0]);  // display the tenth digit
    segment[i % 10](display[1]);  // display the unit digit
    delay(1000);
    Off();
  }
}

/********************************************************************************************/
