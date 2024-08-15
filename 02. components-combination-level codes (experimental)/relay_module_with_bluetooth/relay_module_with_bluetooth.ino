/* This script controls the relay module with the bluetooth. 
We can open a light bulb connected to the relay with this script. */


#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(5, 6); // pass the bluetooth pins

int light = 7;  // relay that connects to a light bulb (can be anything)


void setup() {
  my_bluetooth.begin(9600);
  pinMode(light, OUTPUT);
}


void loop() {
  if (my_bluetooth.available()) {  // Check if data is available
    char a = my_bluetooth.read();
    if (a == 'A') {
      digitalWrite(light, HIGH);
    } else if (a == 'B') {
      digitalWrite(light, LOW);
    }
  }
}