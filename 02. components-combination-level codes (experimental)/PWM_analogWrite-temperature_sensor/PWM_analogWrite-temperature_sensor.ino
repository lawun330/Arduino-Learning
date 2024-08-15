/* This script combins a temperature sensor (usually LM35) and the analog-write function. 
It maps the celsius values to the analog values using the "pulse-width modulation (PWM)" technique. 
The LED will either brights up and fades away based on the temperature. */


int led = 3;
int temp_sensor = A0;

int value;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void loop() {
  float temp = analogRead(temp_sensor);
  temp = temp * 0.48828125;  // convert to celsius
  Serial.println(temp);

  value = map(temp, 20, 80, 0, 255);  // map values from 20*C~80*C to 0~255
  analogWrite(led, value);            // LED brightness is dependent on the temperature
  delay(300);
}
