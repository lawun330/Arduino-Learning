/* The script uses the relay module and the LDR to automate the room lighting. 
If the room is dark, light up a bulb with the relay module. */


int light_pin = 6;
int ldr_pin = A0;


void setup() {
  Serial.begin(9600);
  pinMode(light_pin, OUTPUT);
}


void loop() {
  float brightness = analogRead(ldr_pin);
  Serial.println(brightness);
  delay(300);

  if (brightness < 50) {
    digitalWrite(light_pin, 1);
  } else {
    digitalWrite(light_pin, 0);
  }
}
