/* This script creates specific LED patterns designed to match with Avicii's famous song: Levels. 
I created this script as a tribute to his death, in 2019. 
The patterns are manually implemented. */


int pin;


void setup() {
  for (pin = 2; pin <= 7; pin++) {  // LEDs are connected to pins 2 to 7
    pinMode(pin, OUTPUT);
  }
}


void loop() {
  // 1
  for (int i = 0; i < 9; i++) {
    for (pin = 7; pin >= 2; pin--) {
      digitalWrite(pin, HIGH);
      delay(280);
      digitalWrite(pin, LOW);
    }
    delay(200);
    for (int i = 0; i < 2; i++) {
      digitalWrite(6, HIGH);
      delay(200);

      digitalWrite(5, HIGH);
      delay(200);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      delay(25);
    }

    digitalWrite(6, HIGH);

    digitalWrite(5, HIGH);

    digitalWrite(4, HIGH);
    delay(300);
    digitalWrite(3, HIGH);
    delay(300);

    digitalWrite(7, HIGH);
    delay(300);
    digitalWrite(2, HIGH);
    delay(300);

    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    // 2
    for (pin = 7; pin >= 2; pin--) {
      digitalWrite(pin, HIGH);
      delay(280);
      digitalWrite(pin, LOW);
    }

    for (int i = 0; i < 2; i++) {
      digitalWrite(6, HIGH);
      delay(200);

      digitalWrite(5, HIGH);
      delay(200);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      delay(25);
    }

    digitalWrite(7, HIGH);
    delay(280);
    digitalWrite(4, HIGH);
    delay(280);

    digitalWrite(6, HIGH);
    delay(280);
    digitalWrite(5, HIGH);
    delay(280);

    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }

  for (pin = 7; pin >= 5; pin--) {
    digitalWrite(pin, HIGH);
    delay(280);
    digitalWrite(pin, LOW);
  }

  for (int i = 0; i < 17; i++) {
    digitalWrite(4, HIGH);
    delay(280);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(280);
    digitalWrite(3, LOW);
  }
}
