/* This script commands the LEDs via the bluetooth.
A character, sent by the bluetooth device, toggles the current state of the corresponding LED.
This means - The LED will turn off if it is already turned on.
           - The LED will turn on if it is already turned off. */


#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(10, 11);  // pass bluetooth pins

int redLED = 5;
int blueLED = 6;
int greenLED = 7;
bool redLED_state = 0;
bool blueLED_state = 0;
bool greenLED_state = 0;


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}


void loop() {
  if (my_bluetooth.available()) {   // if bluetooth is available to connect
    char ch = my_bluetooth.read();  // read character from bluetooth
    Serial.println(ch);             // serial display

    // red LED
    if (ch == 'A') {                 // for character 'A'
      redLED_state = !redLED_state;  // toggle the state
      digitalWrite(redLED, redLED_state);
    }

    // blue LED
    else if (ch == 'B') {              // for character 'B'
      blueLED_state = !blueLED_state;  // toggle the state
      digitalWrite(blueLED, blueLED_state);
    }

    // green LED
    else if (ch == 'C') {                // for character 'C'
      greenLED_state = !greenLED_state;  // toggle the state
      digitalWrite(greenLED, greenLED_state);
    }
  }
}
