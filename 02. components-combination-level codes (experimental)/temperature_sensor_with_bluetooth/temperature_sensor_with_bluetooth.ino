/* This script reads the temperature in celsius and sends data to the bluetooth connected device. */


#include <SoftwareSerial.h>

#define TEMPERATURE_SENSOR_PIN A0

SoftwareSerial my_bluetooth(3, 2);  // pass bluetooth pins


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication
}


void loop() {
  float temp = analogRead(TEMPERATURE_SENSOR_PIN);
  temp = temp * 0.48828125;  // convert to celsius
  Serial.print(temp);
  Serial.println(" *C");

  delay(500);

  my_bluetooth.print(temp);  // send data to bluetooth
  my_bluetooth.println(" *C");
}
