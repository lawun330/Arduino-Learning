/* This script demonstrates how to use the pullup button.
It reads the button state every 1s.
Pullup --> Default State: HIGH (VCC) */


int button_pin = 2;


void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);  // input that uses an internal resistor
}


void loop() {
  bool button_state = digitalRead(button_pin);
  Serial.println(button_state);
  delay(1000);
}
