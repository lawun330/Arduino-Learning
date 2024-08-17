/* This script echoes the character sent to the serial port.
This script demonstrates how to talk to Arduino with the serial input. 
The data type used here is "char" data type. 
Test this by writing a character in the serial input and see the character echoed back to you on the serial output. */


void setup() {
  Serial.begin(9600);  // initialize serial communication
}


void loop() {
  if (Serial.available()) {   // if serial communication is ready
    char ch = Serial.read();  // read data
    Serial.println(ch);       // print data
  }
}
