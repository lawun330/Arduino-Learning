/* This script demonstrates the use of the CheapStepper library to control a smaller stepper motor (28BYJ-48).
 * This stepper motor has 4096 steps for a full rotation and 2048 steps for half.
 * 0-360 degree is mapped to 0-4096. 
 * However 2048 is almost the limit. Moving to 2048 is equal to 180 degree. 
 * Setting to 0 or 4096 won't work.
 * moveDegrees() function move argument degrees from a previous position. */


#include <CheapStepper.h>

CheapStepper 28BYJ48_stepper(6, 7, 8, 9);   // pass (IN1, IN2, IN3, IN4) to the constructor


void setup() {
  Serial.begin(9600);
  28BYJ48_stepper.setRpm(12);               // set RPM
  28BYJ48_stepper.moveTo(true, 4096);       // true means counterclockwise
  delay(1000);
  28BYJ48_stepper.moveDegrees(false, 270);  // false means clockwise
}


void loop() {}
