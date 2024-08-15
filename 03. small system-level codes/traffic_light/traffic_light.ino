/* This script mimics a real-world traffic light using one 7-segment display and 3 LEDs.
Like in the real-world, there are three colors: green, yellow, and red.
The maximum countdown is 10s. If we add another 7-segment diplay, we can increase that time. */


#define segA 6   // connecting segment A
#define segB 7   // connecting segment B
#define segC 8   // connecting segment C
#define segD 12  // connecting segment D
#define segE 11  // connecting segment E
#define segF 5   // connecting segment F
#define segG 10  // connecting segment G

int redLED = 2;
int yellowLED = 3;
int greenLED = 4;

int redTime_in_seconds = 10;    // red light for 10s
int yellowTime_in_seconds = 3;  // yellow light for 3s
int greenTime_in_seconds = 10;  // green light for 10s


void setup() {
  for (int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);  // all pins are output
  }
}


void loop() {
  // green light
  digitalWrite(greenLED, 1);
  digitalWrite(yellowLED, 0);
  digitalWrite(redLED, 0);
  countdown(greenTime_in_seconds);
    // end green light

    // yellow light
    digitalWrite(greenLED, 0);
  digitalWrite(yellowLED, 1);
  digitalWrite(redLED, 0);
  countdown(yellowTime_in_seconds);
    // end yellow light

    // red light
    digitalWrite(greenLED, 0);
  digitalWrite(yellowLED, 0);
  digitalWrite(redLED, 1);
  countdown(redTime_in_seconds);
  // end red light
}


// function to show '0' on the display
void zero() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
}


// function to show '1' on the display
void one() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}


// function to show '2' on the display
void two() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}


// function to show '3' on the display
void three() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}


// function to show '4' on the display
void four() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show '5' on the display
void five() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show '6' on the display
void six() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show '7' on the display
void seven() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}


// function to show '8' on the display
void eight() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to show '9' on the display
void nine() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}


// function to reset display
void DisplayOff() {
  digitalWrite(segA, 0);
  digitalWrite(segB, 0);
  digitalWrite(segC, 0);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
}


// function to show a corresponding number on the display
void displayNumber(int num) {
  switch (num) {
    case 0: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
  }
}


// function to count seconds like traffic light
void countdown(int seconds) {
  for (int i = seconds; i >= 0; i--) {
    displayNumber(i);
    delay(1000);
    DisplayOff();
  }
}
