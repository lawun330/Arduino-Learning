/* This script controls a servo motor with the potentiometer. */


#include "Servo.h"

Servo my_servo;

int potentio_pin = A0;
int servo_pin = 10;


void setup() {
  Serial.begin(9600);
  my_servo.attach(servo_pin);
  pinMode(potentio_pin, INPUT);
}


void loop() {
  float analog_value = analogRead(potentio_pin);  // values measured by the potentiometer
  Serial.println(analog_value);

  float angle = map(analog_value, 0, 1023, 0, 180); // map values to specific angles
  Serial.println(angle);

  my_servo.write(angle);  // shift servo angle
}
