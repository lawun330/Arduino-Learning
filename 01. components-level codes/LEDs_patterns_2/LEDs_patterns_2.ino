/* This script demonstrates how to use LEDs with the Arduino with both digital and analog [pulse-width modulation (PWM)] outputs.
There are 9 different patterns that the LEDs can perform. */

int leds[] = { 5, 6, 9, 10, 11 };

void setup() {
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    pinMode(leds[i], OUTPUT);
  }
}


void loop() {
  oneByOne(2);
  allOn();
  allOff();
  twoVsThree(3);
  irregularPatterns();
  oscillation(6);
  dimAndBright(5);
  toTheMiddle(3);
  randomPattern(2);
  allOff();
}


// function to turn all LEDs on
void allOn() {
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(100);
}


// function to turn all LEDs off
void allOff() {
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(100);
}


// function to turn LEDs on one by one
void oneByOne(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = sizeof(leds) / sizeof(leds[0]) - 1; j >= 0; j--) {
      digitalWrite(leds[j], HIGH);
      delay(100);
    }
    for (int j = 0; j < sizeof(leds) / sizeof(leds[0]); j++) {
      digitalWrite(leds[j], LOW);
      delay(100);
    }
  }
}


// function to turn LEDs on two by two and three by three
void twoVsThree(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < sizeof(leds) / sizeof(leds[0]); j += 2) {
      digitalWrite(leds[j], HIGH);
      if (j + 1 < sizeof(leds) / sizeof(leds[0])) {
        digitalWrite(leds[j + 1], LOW);
      }
    }
    delay(100);
    for (int j = 0; j < sizeof(leds) / sizeof(leds[0]); j += 2) {
      digitalWrite(leds[j], LOW);
      if (j + 1 < sizeof(leds) / sizeof(leds[0])) {
        digitalWrite(leds[j + 1], HIGH);
      }
    }
    delay(100);
  }
}


// function to turn LEDs on irregular patterns
void irregularPatterns() {
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);
  digitalWrite(leds[4], HIGH);
  delay(100);

  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);
  digitalWrite(leds[4], HIGH);
  delay(100);

  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], LOW);
  digitalWrite(leds[4], LOW);
  delay(100);

  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], HIGH);
  digitalWrite(leds[4], HIGH);
  delay(100);

  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);
  digitalWrite(leds[4], LOW);
  delay(100);
}


// function to turn LEDs on oscillation
void oscillation(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < sizeof(leds) / sizeof(leds[0]); j++) {
      digitalWrite(leds[j], HIGH);
      delay(50);
      digitalWrite(leds[j], LOW);
    }
    for (int j = sizeof(leds) / sizeof(leds[0]) - 1; j >= 0; j--) {
      digitalWrite(leds[j], HIGH);
      delay(50);
      digitalWrite(leds[j], LOW);
    }
  }
}


// function to turn LEDs on dim and bright
void dimAndBright(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 50; j <= 200; j++) {
      int u = 250 - j;
      for (int k = 0; k < sizeof(leds) / sizeof(leds[0]); k++) {
        analogWrite(leds[k], (k % 2 == 0) ? j : u);
      }
      delay(3);
    }

    for (int j = 200; j >= 50; j--) {
      int u = 250 - j;
      for (int k = 0; k < sizeof(leds) / sizeof(leds[0]); k++) {
        analogWrite(leds[k], (k % 2 == 0) ? j : u);
      }
      delay(3);
    }
  }
}


// function to turn LEDs on to the middle
void toTheMiddle(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < 2; j++) {
      digitalWrite(leds[j], HIGH);
      digitalWrite(leds[4 - j], HIGH);
      delay(100);
    }
    digitalWrite(leds[2], HIGH);
    delay(100);

    digitalWrite(leds[2], LOW);
    delay(100);

    for (int j = 1; j >= 0; j--) {
      digitalWrite(leds[j], LOW);
      digitalWrite(leds[4 - j], LOW);
      delay(100);
    }
  }
}


// function to turn LEDs on random pattern
void randomPattern(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < sizeof(leds) / sizeof(leds[0]); j++) {
      for (int k = 0; k < sizeof(leds) / sizeof(leds[0]); k++) {
        digitalWrite(leds[k], HIGH);
        delay(100);
        digitalWrite(leds[k], LOW);
      }
      digitalWrite(leds[j], HIGH);
      delay(300);
    }
  }
}
