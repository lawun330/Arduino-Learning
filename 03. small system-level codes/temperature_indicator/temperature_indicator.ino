/* This script creates a temperature indicator like a speedometer.
It is constructed via a servo and two temperature sensors (LM35 and DHT11). 
The temperature is averaged and mapped to a specific angle using the map function. 
The temperature is also displayed on the serial monitor. 
That angle is used to move a servo. */


#include "Servo.h"
#include <DHT.h>

Servo pointer;
DHT my_dht(7, DHT11);  // pass the DHT pin

int greenLED = 3;  // indicator LED
int servo_pin = 10;
int temperature_sensor_pin = A0;


void setup() {
  Serial.begin(9600);
  my_dht.begin();
  pointer.attach(servo_pin);
  pinMode(greenLED, OUTPUT);

  digitalWrite(greenLED, HIGH);  // turn the indicator LED on
}


void loop() {
  delay(2000);                             // DHT needs 2s to read temperature
  float dtemp = my_dht.readTemperature();  // temperature measured by the DHT sensor
  Serial.print("DHT measures ");
  Serial.print(dhttemp);

  float LMtemp = analogRead(temperature_sensor_pin);  // temperature measured by the LM35
  LMtemp = LMtemp * 0.48828125;                       // convert to celsius
  Serial.print("*C  LM35 measures ");
  Serial.print(LMtemp);

  float avgtemp = (dhttemp + LMtemp) / 2;  // average temperature
  Serial.print("*C  Average temperature: ");
  Serial.print(avgtemp);
  Serial.println("*C");

  if (avgtemp < 10) {             // 10*C is impossible # incorrect reading
    digitalWrite(greenLED, LOW);  // turn the indicator LED off
  }

  else {
    digitalWrite(greenLED, HIGH);
    float servo_angle = map(avgtemp, 25, 45, 180, 8);  // map temperatures to specific angles # adjust these
    pointer.write(servo_angle);
  }
}
