/* This script is the basic use of Bluetooth module, L293D and two motors (used as wheels).
The Bluetooth module controls the car's movement.
It has five driving modes: Forward, Backward, Left, Right, and Stop.
The Bluetooth module is connected to the Arduino via the SoftwareSerial library. */

#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(10, 11);

int left_wheel_forward_pin = 7;
int left_wheel_backward_pin = 6;
int right_wheel_forward_pin = 5;
int right_wheel_backward_pin = 4;


void setup() {
  Serial.begin(9600);        // initialize the serial communication
  my_bluetooth.begin(9600);  // initialize the bluetooth communication

  pinMode(left_wheel_forward_pin, OUTPUT);
  pinMode(left_wheel_backward_pin, OUTPUT);
  pinMode(right_wheel_forward_pin, OUTPUT);
  pinMode(right_wheel_backward_pin, OUTPUT);
}


void loop() {
  if (my_bluetooth.available()) {   // if bluetooth is available
    char ch = my_bluetooth.read();  // read the character
    Serial.println(ch);             // print the character

    // stop all motors before changing direction
    digitalWrite(left_wheel_forward_pin, 0);
    digitalWrite(left_wheel_backward_pin, 0);
    digitalWrite(right_wheel_forward_pin, 0);
    digitalWrite(right_wheel_backward_pin, 0);

    // drive forward
    while (ch == 'F') {
      digitalWrite(left_wheel_forward_pin, 1);
      digitalWrite(right_wheel_forward_pin, 1);
      break;
    }

    // drive backward
    while (ch == 'B') {
      digitalWrite(left_wheel_backward_pin, 1);
      digitalWrite(right_wheel_backward_pin, 1);
      break;
    }

    // turn left
    while (ch == 'L') {
      digitalWrite(left_wheel_backward_pin, 1);
      digitalWrite(right_wheel_forward_pin, 1);
      break;
    }

    // turn right
    while (ch == 'R') {
      digitalWrite(left_wheel_forward_pin, 1);
      digitalWrite(right_wheel_backward_pin, 1);
      break;
    }

    // stop
    while (ch == 'S') {
      digitalWrite(left_wheel_forward_pin, 0);
      digitalWrite(left_wheel_backward_pin, 0);
      digitalWrite(right_wheel_forward_pin, 0);
      digitalWrite(right_wheel_backward_pin, 0);
      break;
    }
  }
}
