/* In Arduino, the loop() function cannot be ended. 
This script creates an effect of ending that loop by entering an infinite empty loop. */


bool no_loop = false;


void setup() {
  Serial.begin(9600);
}


void loop() {
  no_loop = true;
  Serial.print("The loop ends after this line");
  while (no_loop) {}  // do nothing indefinitely
}
