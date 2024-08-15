/* This script combines the temperature sensor (usually LM35) and flame sensor. 
It can be used to detect fire and aircon failure. */


int temperature_sensor_pin = A0;
int flame_sensor_pin = A1;


void setup() {
  Serial.begin(9600);
  pinMode(temperature_sensor_pin, INPUT);
  pinMode(flame_sensor_pin, INPUT);
}


void loop() {
  float temperature = analogRead(temperature_sensor_pin);
  temperature = temperature * 0.48828125; // convert to celsius

  float flame = analogRead(flame_sensor_pin);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("*C Flame: ");
  Serial.println(flame);

  if (temperature < 30 && flame > 300) {
    Serial.println("Everything is fine.");
  } else if (temperature > 50 && flame < 300) {
    Serial.println("Fire detected.");
  } else if (temperature > 40 && flame > 300) {
    Serial.println("Aircon has stopped functioning.");
  }
  
  Serial.println();
  delay(2000);
}
