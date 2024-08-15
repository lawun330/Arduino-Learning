/*
  This script is designed to interface with an ESP8266 WiFi module and send data to the ThingSpeak API.
  It reads data from analog sensors connected to the Arduino, generates a random value, and sends these values to the ThingSpeak server.

  Key components of the script:
  - SoftwareSerial library is used to communicate with the ESP8266 module.
  - WiFi credentials (SSID and Password) are defined to connect to the WiFi network.
  - ThingSpeak API key and host details are defined for data transmission.
  - The setup() function initializes serial communication and connects to the WiFi network.
  - The loop() function reads sensor data, generates a random value, and sends these values to the ThingSpeak API.

  Detailed steps in the script:
  1. Initialize serial communication with the ESP8266 module.
  2. Reset the ESP8266 module and set it to station mode.
  3. Connect to the specified WiFi network using the provided SSID and password.
  4. In the loop, read data from analog sensors (A0 and A1).
  5. Generate a random value between 1 and 1000.
  6. Construct the data string to be sent to the ThingSpeak API.
  7. Configure the ESP8266 for multiple connections and start a TCP connection to the ThingSpeak server.
  8. Send the constructed data string to the ThingSpeak server.
  9. Print the value being sent to the serial monitor for debugging purposes.

  Note: The analogRead() functions are used to read data from the sensors connected to the Arduino.
  The temperature value is scaled using a factor of 0.8266 to convert the raw analog reading to a meaningful value.
  The ldr value is read directly from the analog pin A1.
*/


#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);  // pins 2 and 3 act as RX and TX # connect them to TX and RX of ESP8266

#define DEBUG true
#define TEMPERATURE_SENSOR_PIN A0
#define LDR_PIN A1

String mySSID = "MAR-LX2";          // WiFi SSID
String myPWD = "helloworld";        // WiFi Password
String myAPI = "EX8FZ8HZLJMKDKOS";  // API Key
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String myFIELD = "field1";
String myFIELD2 = "field2";
String myFIELD3 = "field3";

int sendVal;
float temperature;
float ldr;


void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);

  espData("AT+RST", 1000, DEBUG);                                         // reset the ESP8266 module
  espData("AT+CWMODE=1", 1000, DEBUG);                                    // set the ESP mode as station mode
  espData("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 1000, DEBUG);  // connect to WiFi network
  while (!esp.find("OK")) {
    //Wait for connection
  }
  delay(1000);
}


void loop() {
  sendVal = random(1000);                                         // change this to sensor's readings
  temperature = analogRead(TEMPERATURE_SENSOR_PIN) * 0.48828125;  // temperature sensor readings
  ldr = analogRead(LDR_PIN);                                      // LDR sensor readings

  String sendData = "GET /update?api_key=" + myAPI + "&" + myFIELD + "=" + String(sendVal) + "&" + myFIELD2 + "=" + String(temperature) + "&" + myFIELD3 + "=" + String(ldr);

  espData("AT+CIPMUX=1", 1000, DEBUG);  // allow multiple connections
  espData("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);
  espSerial.find(">");
  espSerial.println(sendData);
  Serial.print("Value to be sent: ");
  Serial.println(sendVal);

  espData("AT+CIPCLOSE=0", 1000, DEBUG);
  delay(10000);
}


// function to send AT commands to the ESP8266 module
String espData(String command, const int timeout, boolean debug) {
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");

  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (espSerial.available()) {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}
