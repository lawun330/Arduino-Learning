/* This script combines the pulldown button, the potentiometer (it can be any input reader), and the analog-write function. 
Values are read only if the button is pressed (the switch is on). 
The LED either brights up and fades away based on the potentiometer's value. 
Pulldown --> Default State: LOW (Ground) */


int button_pin = 3;
int potentio_pin = A0;
int led = 10;


void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led, OUTPUT);
}


void loop() {
  bool button_state = digitalRead(button_pin);

  if (button_state == 1) {                    // if the button is pressed
    potentio_val = analogRead(potentio_pin);  // read values
    value = map(potentio_val, 0, 1023, 0, 255);
    analogWrite(led, value);
  }

  else if (button_state == 0) {  // if the button is not pressed // no value is read
    digitalWrite(led, LOW);
  }
}
