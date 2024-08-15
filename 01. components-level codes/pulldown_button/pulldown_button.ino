/* This script demonstrates how to use the pulldown button.
It reads the button state every 1s. 
Pulldown --> Default State: LOW (Ground) */


int button_pin = 2;


void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);  // normal input that uses an external resistor
}


void loop() {
  bool button_state = digitalRead(button_pin);
  Serial.println(button_state);
  delay(1000);
}
