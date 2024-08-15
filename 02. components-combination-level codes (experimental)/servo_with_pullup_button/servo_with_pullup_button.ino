/* This script controls the servo with the pullup button. 
Pullup --> Default State: HIGH (VCC) */


#include "Servo.h"

Servo my_servo;

int servo_pin = 11;
int button_pin = 9;


void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
  my_servo.attach(servo_pin);
}


void loop() {
  bool button_state = digitalRead(button_pin);
  Serial.println(button_state);

  if (button_state == HIGH) {  // rotate to the angle 0*
    my_servo.write(0);
  }

  else if (button_state == LOW) {  // rotate to the angle 180*
    my_servo.write(180);
  }
}
