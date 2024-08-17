/* This script is used to debounce a button.
Suppose we want to turn things on and off by pressing a button.
The button state 'TRUE' is read multiple times (noises) even if the button is pressed for a single time.
This makes it hard to turn things on and off.
To fix this, we can store the previous button state.
If the current state is true and the previous state is false, this means the button is actually pressed once.
Even if there are multiple 'TRUE' readings, the previous state helps us distinguish between the actual button press and the noise.
The debouncing is done this way. 
The LED is toggled only if the button is actually pressed. */


#define LED_PIN 3
#define BUTTON_PIN 2

bool previous_button_state = false;
bool trigger = false;  // variable that stores HIGH or LOW


void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}


void loop() {
  bool current_button_state = digitalRead(BUTTON_PIN);
  if (current_button_state && !previous_button_state) {  // if current state is true and previous state is false
    trigger = !trigger;
  }
  previous_button_state = current_button_state;  // update previous state
  digitalWrite(LED_PIN, trigger);                // toggle LED
}
