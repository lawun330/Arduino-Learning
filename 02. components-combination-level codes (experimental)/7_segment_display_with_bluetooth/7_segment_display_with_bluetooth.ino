/* This script commands the 7 segment display via the bluetooth. 
It displays 4 alphabets (A, b, C, d) based on the bluetooth input. */


#include "SoftwareSerial.h"

#define segA 6   // connect segment A
#define segB 7   // connect segment B
#define segC 8   // connect segment C
#define segD 12  // connect segment D
#define segE 11  // connect segment E
#define segF 5   // connect segment F
#define segG 10  // connect segment G

SoftwareSerial my_bluetooth(3, 2);  // pass bluetooth pins


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication

  for (int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);  // display pins are output # for UNO
  }
}


void loop() {
  if (my_bluetooth.available()) {   // if bluetooth is available to connect
    char ch = my_bluetooth.read();  // read character from bluetooth
    Serial.println(ch);             // serial display
    delay(100);

    if (ch == 'A') {  // for character 'A'
      DisplayOff();   // reset display
      delay(100);
      a();  // show 'A' on display
    }

    else if (ch == 'B') {  // for character 'B'
      DisplayOff();        // reset display
      delay(100);
      b();  // show 'b' on display
    }

    else if (ch == 'C') {  // for character 'C'
      DisplayOff();        // reset display
      delay(100);
      c();  // show 'C' on display
    }

    else if (ch == 'D') {  // for character 'D'
      DisplayOff();        // reset display
      delay(100);
      d();  // show 'd' on display
    }

    else {  // for other characters
      DisplayOff();
      Serial.println("Input character cannot be displayed!");
    }
  }
}


// function to show 'A' on display
void a() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show 'b' on display
void b() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show 'C' on display
void c() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
}


// function to show 'd' on display
void d() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}


// function to reset display
void DisplayOff() {
  digitalWrite(segA, 0);
  digitalWrite(segB, 0);
  digitalWrite(segC, 0);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
}
