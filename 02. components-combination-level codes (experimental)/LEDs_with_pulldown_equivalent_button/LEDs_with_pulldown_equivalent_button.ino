/* This script uses the pulldown equivalent button to control 6 LEDs. 
The LEDs are arranged in a line, and the script oscillates through the LEDs to create a flickering effect. 
The button state is read multiple times to shut the LEDs off immediately as soon as the button is released.
Pullup --> Default State: HIGH (VCC)
Pulldown --> Default State: LOW (Ground) 
digitalRead --> pullup
!digitalRead --> pullup but pulldown equivalent */


int button_pin = 8;
bool button_state;
int LEDpins;


void setup() {
  pinMode(button_pin, INPUT_PULLUP);  // pullup button
  for (LEDpins = 2; LEDpins <= 7; LEDpins++) {
    pinMode(LEDpins, OUTPUT);
  }
}


void loop() {
  button_state = !digitalRead(button_pin);  // pullup button is transformed into pulldown equivalent with '!'

  while (button_state == 1) {
    for (int i = 2; i <= 7; i++) {
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
      button_state = !digitalRead(button_pin);  // pullup button is transformed into pulldown equivalent with '!'
      if (button_state == 0) break;
    }
    for (int i = 6; i >= 2; i--) {
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
      button_state = !digitalRead(button_pin);  // pullup button is transformed into pulldown equivalent with '!'
      if (button_state == 0) break;
    }
    break;
  }
}
