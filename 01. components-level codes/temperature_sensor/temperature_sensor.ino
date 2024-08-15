/* This script demonstrates the use of the temperature sensor (usually LM35).
It prints out the temperature values in celsius. */

 
#define TEMPERATURE_SENSOR_PIN A0


void setup() {
  Serial.begin(9600);
}


void loop() {
  float temp = analogRead(TEMPERATURE_SENSOR_PIN);
  temp = temp * 0.48828125;  // convert to celsius
  Serial.println(temp);
  delay(2000);
}
