/* This script echoes the message (String) sent to the serial port.
Normally, we use characters and integers to send data.
This script illustrates how "String" data type can be sent. 
Test this by writing a string in the serial input and see the string echoed back to you on the serial output. */


String message;  // string that stores an incoming serial message


void setup() {
  Serial.begin(9600);
}


void loop() {
  while (Serial.available()) {       // while data is available on the serial
    message += char(Serial.read());  // build a string by adding each character from serial string input
  }
  if (!Serial.available()) {
    if (message != "") {                                      // if data is available
      Serial.print("Your message is received. It is \n>>>");  // wrapper
      Serial.println(message);                                // diplay data
      message = "";                                           // clear data
      Serial.println("Message sent and cleared! \n");         // wrapper
    }
  }
}
