/* This script creates a small fire alarm system by measuring the temperature in celsius.
For temperature, it has two sensors: DHT and temperature sensor (usually LM35).
  - The average temperature is computed from their outputs.
For brightness, it has the LDR.
# Lower temperatures indicate a normal environment.
  - Trigger the green LED.
# Higher temperatures with a bright light indicate a fire.
  - Trigger the red LED and increasing-frequency sound. 
# Higher temperatures without a bright light indicate a hot environment.
  - Trigger the red LED, but no sound alarm. */


#include <DHT.h>

#define TEMPERATURE_SENSOR_PIN A0
#define LDR_PIN A1

DHT my_dht(2, DHT11)  // pass the DHT pin

int ledG = 8;
int ledR = 7;
int buzzer = 5;  // buzzer connected to PWM digital pin


void setup() {
  Serial.begin(9600);
  my_dht.begin();
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
}


void loop() {
  float ldr = analogRead(LDR_PIN);  // brightness value measured by the LDR sensor

  float temp = analogRead(TEMPERATURE_SENSOR_PIN);  // temperature measured by the LM35
  temp = temp * 0.48828125;                         // convert to celsius

  delay(2000);                             // sometimes, DHT needs 2s to read data
  float dtemp = my_dht.readTemperature();  // temperature measured by the DHT sensor
  float dhum = my_dht.readHumidity();      // humidity measured by the DHT sensor

  float avgtemp = (temp + dtemp) / 2;  // average temperature

  Serial.print("Temperature: ");
  Serial.print(avgtemp);
  Serial.print("*C  LDR: ");
  Serial.print(ldr);
  Serial.print("  Humidity: ");
  Serial.println(dhum);

  if (avgtemp < 40) {          // under 40* C
    digitalWrite(ledG, HIGH);  // green LED to indicate a normal environment
    digitalWrite(ledR, LOW);   // no red LED
    noTone(buzzer);            // no sound alarm
  }

  else if (avgtemp > 40) {     // over 40* C
    digitalWrite(ledR, HIGH);  // red LED to indicate a hot environment
    digitalWrite(ledG, LOW);   // no green LED

    if (ldr > 500) {                      // significantly bright
      for (int i = 200; i <= 800; i++) {  // trigger sound alarm # frequency increasing
        tone(buzzer, i);
        delay(buzzer);
      }
      delay(1000);
    }

    else {             // no significant brightness apart from possible daylight
      noTone(buzzer);  // no sound alarm
    }
  }
}
