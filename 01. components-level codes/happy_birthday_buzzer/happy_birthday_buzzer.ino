/* This script implements specific frequency values to produce "Happy Birthday" song with the buzzer. */


int buzzer = 5;  // buzzer connected to PWM digital pin

// Note frequencies
const int C4 = 261;
const int D4 = 293;
const int E4 = 329;
const int F4 = 349;
const int G4 = 391;
const int a4 = 440;  // distinguish it from analog A4 pin
const int Bb4 = 466;
const int C5 = 523;

// Note durations
const int QUARTER = 500;
const int EIGHTH = 250;
const int SIXTEENTH = 125;

// Song notes and durations
int melody[] = {
  C4, QUARTER, C4, EIGHTH, D4, QUARTER, C4, QUARTER, F4, QUARTER, E4, QUARTER,
  C4, QUARTER, C4, EIGHTH, D4, QUARTER, C4, QUARTER, G4, QUARTER, F4, QUARTER,
  C4, QUARTER, C4, EIGHTH, C5, QUARTER, a4, QUARTER, F4, QUARTER, E4, QUARTER, D4, QUARTER,
  Bb4, QUARTER, Bb4, EIGHTH, a4, QUARTER, F4, QUARTER, G4, QUARTER, F4, QUARTER
};


void setup() {
  pinMode(buzzer, OUTPUT);
}


void loop() {
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i += 2) {
    tone(buzzer, melody[i]);
    delay(melody[i + 1] * 0.8);  // add a small delay between notes
  }
  noTone(buzzer);  // stop the tone when done
  delay(2000);     // wait before repeating the song
}
