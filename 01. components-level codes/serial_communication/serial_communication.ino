/* This script demonstrates how to talk to Arduino with the serial input. */


void setup() {
  Serial.begin(9600);  // initialize serial communication
}


void loop() {
  if (Serial.available()) {   // if serial communication is ready
    char ch = Serial.read();  // read data
    Serial.println(ch);       // print data
  }
}
