/* This script combins a potentiometer and the analog-write function. 
It maps the values read by potentiometer to the analog values using the "pulse-width modulation (PWM)" technique. 
The LED either brights up and fades away based on the potentiometer's value.
The volume of the buzzer is dependent on the potentiometer's value. */


int led_pin = 3;
int buzzer_pin = 5;  // buzzer connected to PWM digital pin
int potentio_pin = A0;

int value;


void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
}


void loop() {
  float potentio_value = analogRead(potentio_pin);  // read values from the potentiometer

  value = map(potentio_value, 0, 1023, 0, 255);  // LED is 0 - 255
  analogWrite(led_pin, value);
  value = map(potentio_value, 0, 1023, 0, 800);  // buzzer is 0 - 800
  analogWrite(buzzer_pin, value);
  delay(300);
}
