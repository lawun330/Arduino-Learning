/*
  Stopwatch Script for Arduino

  This script is designed to function as a stopwatch using an Arduino board. 
  It utilizes a 4-channel 7-segment display, 2 buttons, and a buzzer to provide 
  a fully functional stopwatch experience. The stopwatch can be started, paused, 
  reset, and closed as needed.

  Components:
  - 4-channel 7-segment display
  - 2 buttons
  - 1 buzzer

  The buttons are used to start, pause, and reset the stopwatch. 

  Functionality:
  - **Start the Stopwatch**: 
    - **Button A**: Starts the stopwatch on the first press.
    - **Code**: The `keepRunning()` function is called to start the timer and display the time.
  - **Pause the Stopwatch**: 
    - **Button B**: Pauses the stopwatch when pressed.
    - **Code**: The `pause()` function is called to stop the timer and display the current time.
  - **Resume the Stopwatch**: 
    - **Button A**: Resumes the stopwatch after it has been paused.
    - **Code**: The `keepRunning()` function is called again to resume the timer.
  - **Reset the Stopwatch**: 
    - **Both Buttons A and B**: Resets the stopwatch to zero.
    - **Code**: The `reset()` function is called to reset the display and variables.
  - **Stop the Stopwatch**: 
    - **Both Buttons A and B**: Stops the stopwatch and turns off all LEDs.
    - **Code**: The `stopAll()` function is called to stop the timer, turn off the display, and reset variables.

  Pinout configuration for the 4-channel 7-segment display:
  - Upper row (from left to right): D1 (thousand digit), A (segment A), F (segment F), D2 (hundred digit), D3 (ten digit), B (segment B)
  - Lower row (from left to right): E (segment E), D (segment D), deci (decimal point), C (segment C), G (segment G), D4 (single digit)
  - Common grounds for the digits are D1 to D4. */


#include <TimerOne.h>

int Up = 6;            // segment A
int Down = 12;         // segment D
int UpL = 5;           // segment F
int DownL = 13;        // segment E
int UpR = 2;           // segment B
int DownR = 10;        // segment C
int Mid = 9;           // segment G
int decimal = 11;      // decimal point
int button_A_pin = 1;    // button A
int button_B_pin = 0;  // button B
int buzzer = A0;       // for buzzer sound

#define D1 7  // thousand digit
#define D2 4  // hundred digit
#define D3 3  // ten digit
#define D4 8  // single digit

int s = -1;
int t = 0;
int h = 0;
int T = 0;
int x = 0;


void setup() {
  Serial.begin(9600);
  for (int pin = 2; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(buzzer, OUTPUT);
  pinMode(button_A_pin, INPUT_PULLUP);
  pinMode(button_B_pin, INPUT_PULLUP);
}


void loop() {
  bool button_A_state = !digitalRead(button_A_pin);
  delay(500);

  // the timer starts with the first press on button A
  while (button_A_state == HIGH) {
    button_A_state = !digitalRead(button_A_pin);
    bool button_B_state = !digitalRead(button_B_pin);

    // keep running without any press
    /* # buttons usually go back to LOW after it is pressed.
       # variable 'x' is used to store the state.
       # 'x' distinguishes between 'button B never pressed before' and 'button B after pressed' states.
    */
    if (button_A_state == LOW && button_B_state == LOW && x == 0) { // 'x' = 0 for 'button B never pressed before'
      keepRunning();
    }

    // press button B to pause
    while (button_A_state == LOW && button_B_state == HIGH) {
      x = 1; // 'x' = 1 for 'button B after pressed'
      pause();
      button_A_state = !digitalRead(button_A_pin);

      // press button A to resume
      if (button_A_state == HIGH) {
        button_A_state = LOW;
        button_B_state = LOW;
        x = 0;  
      }
    }

    // press both buttons to stop
    if (button_A_state == HIGH && button_B_state == HIGH) {
      reset();
      delay(1000);
      stopAll();
      return;
    }
  }

  // the timer won't start until the first press on button A
  if (button_A_state == LOW) {
    stopAll();
  }
}

/********************************************************************************************/

// Here, HIGH makes LED off # LOW makes LED on # It is reversed

// function to show '0' on display
void zero() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 0);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 1);
}


// function to show '1' on display
void one() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 1);
  digitalWrite(Down, 1);
  digitalWrite(UpL, 1);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 1);
}


// function to show '2' on display
void two() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 1);
  digitalWrite(DownL, 0);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 1);
  digitalWrite(Mid, 0);
}


// function to show '3' on display
void three() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 1);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to show '4' on display
void four() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 1);
  digitalWrite(Down, 1);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to show '5' on display
void five() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 1);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to show '6' on display
void six() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 0);
  digitalWrite(UpR, 1);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to show '7' on display
void seven() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 1);
  digitalWrite(UpL, 1);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 1);
}


// function to show '8' on display
void eight() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 0);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to show '9' on display
void nine() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 0);
  digitalWrite(Down, 0);
  digitalWrite(UpL, 0);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 0);
  digitalWrite(DownR, 0);
  digitalWrite(Mid, 0);
}


// function to turn off all LEDs
void Off() {
  digitalWrite(decimal, 1);
  digitalWrite(Up, 1);
  digitalWrite(Down, 1);
  digitalWrite(UpL, 1);
  digitalWrite(DownL, 1);
  digitalWrite(UpR, 1);
  digitalWrite(DownR, 1);
  digitalWrite(Mid, 1);
}

/********************************************************************************************/

// function to turn on the buzzer
void buzzOn() {
  digitalWrite(buzzer, HIGH);
  delay(2000);
}


// function to turn off the buzzer
void buzzOff() {
  digitalWrite(buzzer, LOW);
  delay(0);
}

/********************************************************************************************/

// function to start the timer
void startTimer() {
  Timer1.initialize(1000000);                // customize delay in microseconds (1 second for now)
  Timer1.attachInterrupt(incrementCounter);  // pass the (function) as argument for customized delay
  // The attached function 'increamentCounter' will be executed repeatedly after the specified delay
}


// function to increment the counter
void incrementCounter() {
  s++;            // add counter every 1s
  if (s == 10) {  // s for unit digit   // reset when s = 10
    s = 0;
    t++;
    if (t == 10) {  // t for tenth-digit
      t = 0;
      h++;
      if (h == 10) {  // h for hundredth-digit
        T++;
        h = 0;
        if (T == 10) {  // T for thousandth-digit
          T = 0;
        }
      }
    }
  }

  // prepare time value
  int realSeconds = (T * 1000) + (h * 100) + (t * 10) + (s);  // sums up to get real time  // function starts from 1
  int quotient = (realSeconds / 60);                          // divided by 60, then take the natural number
  int remainder = realSeconds - (60 * quotient);              // difference with real time to get remainder

  // an alarm for every minute passed
  if (remainder == 0) {  // if divisible by 60, buzzer beeps
    if (realSeconds > 0) {
      buzzOn();
      buzzOff();
    }
  }
}

/********************************************************************************************/

// function to turn on the custom digit
void ledOn(int k) {
  // turn off all LEDs
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  // turn on the custom digit
  switch (k) {
    default: digitalWrite(D4, HIGH); break;
    case 1: digitalWrite(D1, HIGH); break;
    case 2: digitalWrite(D2, HIGH); break;
    case 3: digitalWrite(D3, HIGH); break;
  }
}


// function to display the numbers
void displayNumber(int y) {
  switch (y) {
    default: zero(); break;
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

/********************************************************************************************/

// function to display the time (s, t, h, T)
void displayTime() {
  Off();
  ledOn(4);
  displayNumber(s);
  delay(5);

  Off();
  ledOn(3);
  displayNumber(t);
  delay(5);

  Off();
  ledOn(2);
  displayNumber(h);
  delay(5);

  Off();
  ledOn(1);
  displayNumber(T);
  delay(5);
}

/********************************************************************************************/

// function to start the stopwatch
void keepRunning() {
  displayTime();
  startTimer();  // start counting
}


// function to pause the stopwatch
void pause() {
  buzzOff();
  Timer1.detachInterrupt();
  displayTime();
}


// function to reset the stopwatch
void reset() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  displayNumber(0);
}


// function to stop everything
void stopAll() {
  Off();
  buzzOff();
  Timer1.detachInterrupt();
  s = -1;
  t = 0;
  h = 0;
  T = 0;
}

/********************************************************************************************/
