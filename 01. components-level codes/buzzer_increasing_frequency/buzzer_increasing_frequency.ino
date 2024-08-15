/* This script demonstrates the use of the buzzer. 
It creates an increasing-frequency sound. */


const int buzz = 3;  // buzzer connected to PWM digital pin


void setup() {
  pinMode(buzz, OUTPUT);
}


void loop() {
  for (int i = 200; i <= 800; i++) {  // define custom frequency range
    tone(buzz, i);                    // pass each frequency
    delay(5);
  }
  delay(1000);
}
