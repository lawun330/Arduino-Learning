/* This script demonstrates how to use LEDs with the Arduino. 
There are 9 different patterns that the LEDs can perform. */


int led1 = 5;
int led2 = 6;
int led3 = 9;
int led4 = 10;
int led5 = 11;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}


void loop() {
  sequence1();
  sequence2();
  sequence3();
  sequence4();
  sequence5();
  wavePattern();
  lastPattern();
  waveLoop();
  finalLoop();
}


// function to perform LEDs pattern 1
void sequence1() {
  for (int i = 5; i >= 1; i--) {
    digitalWrite(ledPin(i), HIGH);
    delay(50);
  }
  for (int i = 1; i <= 5; i++) {
    digitalWrite(ledPin(i), LOW);
    delay(50);
  }
}


// function to perform LEDs pattern 2
void sequence2() {
  all_LEDs(HIGH);
  delay(200);
  all_LEDs(LOW);
  delay(200);
}


// function to perform LEDs pattern 3
void sequence3() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(200);
  }
}


// function to perform LEDs pattern 4
void sequence4() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    delay(200);

    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(200);
  }
}


// function to perform LEDs pattern 5
void sequence5() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    delay(200);
    digitalWrite(led3, HIGH);
    delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(200);
  }
}


// function to perform LEDs pattern 6
void wavePattern() {
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led5, HIGH);
  delay(200);
  digitalWrite(led2, HIGH);
  digitalWrite(led4, HIGH);
  delay(200);
  digitalWrite(led3, HIGH);
  delay(200);

  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led5, LOW);
  delay(200);
}


// function to perform LEDs pattern 7
void lastPattern() {
  all_LEDs(HIGH);
  delay(200);
  all_LEDs(LOW);
  delay(200);
}


// function to perform LEDs pattern 8
void waveLoop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led5, HIGH);
    delay(200);
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led5, LOW);
    digitalWrite(led1, LOW);
    delay(200);
    digitalWrite(led2, HIGH);
    digitalWrite(led4, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    digitalWrite(led4, LOW);
    delay(200);
    digitalWrite(led3, HIGH);
    delay(200);
    digitalWrite(led3, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led4, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    digitalWrite(led4, LOW);
    delay(200);
    digitalWrite(led5, HIGH);
    digitalWrite(led1, HIGH);
    delay(200);
  }
}


// function to perform LEDs pattern 9
void finalLoop() {
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led4, HIGH);
  delay(200);
  all_LEDs(LOW);
  delay(200);
}


// function to dictate all LEDs with the parameter 'state'
void all_LEDs(bool state) {
  digitalWrite(led1, state);
  digitalWrite(led2, state);
  digitalWrite(led3, state);
  digitalWrite(led4, state);
  digitalWrite(led5, state);
}


// function to map logical LED pins to actual physical pin numbers
// logical pins makes it easier to change the order of the LEDs # in for loops
int ledPin(int num) {
  switch (num) {
    case 1: return led1;
    case 2: return led2;
    case 3: return led3;
    case 4: return led4;
    case 5: return led5;
    default: return -1;
  }
}
