/* This script controls the LED lighting duration based on the serial input (serial command line interface). */


int led = 2;


void setup() {
  Serial.begin(9600);
  Serial.println("Welcome");
  pinMode(led, OUTPUT);
}


void loop() {
  if (Serial.available()) {  // if serial input is ready
    Serial.println("How many seconds should the LED light up? <integers>: ");
    int i = Serial.read();  // read an integer
    Serial.println(i);

    digitalWrite(led, HIGH);
    delay(i * 1000);
    digitalWrite(led, LOW);
  }
}
