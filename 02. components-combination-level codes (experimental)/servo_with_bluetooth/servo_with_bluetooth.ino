/* This script controls the servo via the bluetooth. 
The value of the servo degree is given via the bluetooth. */


#include "Servo.h"
#include "SoftwareSerial.h"

Servo my_servo;
SoftwareSerial my_bluetooth(4, 3);  // pass bluetooth pins

int servo_pin = 5;


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication
  my_servo.attach(servo_pin);
}


void loop() {
  if (my_bluetooth.available()) {               // if bluetooth is available to connect
    int bluetooth_input = my_bluetooth.read();  // read character from bluetooth
    Serial.println(bluetooth_input);            // serial display

    int degree = map(bluetooth_input, 0, 9, 0, 180);  // map data to degrees
    my_servo.write(degree);                           // rotate to an arbitrary angle
  }
}
