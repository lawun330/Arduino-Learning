/* This script demonstrates two ways to use the ultrasonic sensor (HCSR04).
- The first method is a conventional use of pulseIn().
- The second method uses the <HC_SR04.h> library.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// first method: conventional use of pulseIn()
// Use pulseIn() if we need to block the program flow unless certain pulse happens.

int echo = 2;
int trig = 11;
float TIME;
float DIS;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);  // only for the first method
  pinMode(echo, INPUT);   // only for the first method
}

void loop() {
  digitalWrite(trig, 0);  // ensure no signal is sent
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // release a signal from the trigger
  delayMicroseconds(10);
  digitalWrite(trig, 0);  // stop releasing

  TIME = pulseIn(echo, 1);  // get the time it takes for that signal to go from the trigger and return to the echo
  DIS = TIME * 0.034 / 2;   // convert to distance from time

  Serial.print("DISTANCE: ");
  Serial.print(DIS);
  Serial.println(" cm");
}
/* NOTES:
 * pulseIn() function can use with HIGH or LOW argument. 
 * But the voltage must be the opposite of that pulseIn argument.
 * The waiting time before pulseIn works is called the parameter "timeOut".
 * The function measures the length of a pulse (HIGH OR LOW) and returns it.
 * The disadvantage of using it is the program stops when it is used. */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* // second method: use library
// Use attachInterrupt() if we want the program to flow continuously.

#include <HC_SR04.h>  // for the second method, import HCSRO4 attachInterrupt library

int echo = 2;  // should be pin 2 or 3 for interrupts on Arduino UNO
int trig = 11;
HC_SR04 my_usonic(trig, echo);

// function to check if the echo is finished
void echoISR() {
  my_usonic.echoCheck();
}

void setup() {
  Serial.begin(9600);
  my_usonic.begin();                                                        // only for the second method
  my_usonic.start();                                                        // only for the second method
  attachInterrupt(digitalPinToInterrupt(echo), echoISR, CHANGE);            // only for the second method
}

void loop() {
  if (my_usonic.isFinished()) {
    // ## do something here ##
    Serial.print(my_usonic.getRange());
    Serial.println("cm");
    delay(50);
    my_usonic.start();
  }
  // ## do other things here while waiting for pulse ##
}
/* NOTES:
 * attachInterrupt() has no delay time unlike pulseIn().
    * attachInterrupt(digitalPinToInterrupt(echo), function_to_use(), CHANGE); // put this in the setup
    * echo pin should be digital pin 2 or 3 in arduino UNO since they are applicable for interrupts.
    * attachInterrupt(pin, function, parameter).
 * Some functions from <HC_SR04.h>
    * my_usonic.start();
    * my_usonic.begin();
    * my_usonic.isFinished();
    * my_usonic.getRange(); //get range in cm
    * my_usonic.getRange(INCH); */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////