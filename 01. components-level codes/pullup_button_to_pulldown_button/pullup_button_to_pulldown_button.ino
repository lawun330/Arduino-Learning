/* This script demonstrates how to convert the pullup button to the pulldown button.
It reads the button state every 1s.
Pullup --> Default State: HIGH (VCC)
Pulldown --> Default State: LOW (Ground) 
digitalRead --> pullup
!digitalRead --> pullup but pulldown equivalent */


int button_pin = 2;


void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);  // input that uses an internal resistor
}


void loop() {
  bool button_state = !digitalRead(button_pin);  // add ! to change
  Serial.println(button_state);
  delay(1000);
}
