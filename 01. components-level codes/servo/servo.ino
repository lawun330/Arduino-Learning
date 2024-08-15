/* This script demostrates the basic use of a servo motor. It can be used to calibrate an angle. */


#include <Servo.h>

Servo my_servo;

int servo_pin = 10;


void setup() {
  my_servo.attach(servo_pin);
}


void loop() {
  my_servo.write(180);
}
