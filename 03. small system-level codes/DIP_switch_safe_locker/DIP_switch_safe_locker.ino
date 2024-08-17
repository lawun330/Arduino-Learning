/* This script creates a safe locker using two DIP switches (SPST x 4), a button, and a buzzer.
 * 
 * Instructions:
 * - Change the password by editing the 'password' string.
 *   - The password must be 8 digits long.
 *   - The password cannot be all zeros or all ones.
 * - The input is read from the switches whenever the button is pressed.
 * - One attempt is reduced per button press.
 *   - Change the number of attempts by editing the 'remaining_attempts' value.
 * - If the input is incorrect for the maximum number of attempts, the buzzer will beep and the locker remains locked.
 * - Once all attempts are used, there is no way to reset the attempts.
 * - If attempts remain, the locker will unlock when the correct password is entered. */


#define switch_1_pin 10
#define switch_2_pin 9
#define switch_3_pin 8
#define switch_4_pin 7
#define switch_5_pin 5
#define switch_6_pin 4
#define switch_7_pin 3
#define switch_8_pin 2
#define confirm_button_pin 12
#define buzzer 6

// variables
#define MAX_PASSWORD_DIGIT 8   // number of digits in the password # corresponds to the number of switches
int remaining_attempts = 3;    // maximum number of attempts allowed
String password = "10010010";  // enter your password (in binary) here
int switch_pins[MAX_PASSWORD_DIGIT] = { switch_1_pin, switch_2_pin, switch_3_pin, switch_4_pin,
                                        switch_5_pin, switch_6_pin, switch_7_pin, switch_8_pin };  // pins
int password_combination[MAX_PASSWORD_DIGIT];                                                      // password combination of 0s and 1s
int input_combination[MAX_PASSWORD_DIGIT];                                                         // input combination of 0s and 1s
bool unlock = false;                                                                               // if the locker is ready to unlock or not


void setup() {
  Serial.begin(9600);
  Serial.println("GUESS THE PASSWORD");
  for (int i = 0; i < MAX_PASSWORD_DIGIT; i++) {
    pinMode(switch_pins[i], INPUT_PULLUP);
  }
  pinMode(confirm_button_pin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);  // no alarm at the start
}


void loop() {
  setPasswordArray(password);  // prepare the first array: password combination

  Serial.println("Remaining attempts:" + String(remaining_attempts));  // debug print

  if (!digitalRead(confirm_button_pin)) {                                 // whenever a button is pressed
    getCurrentInput();                                                    // prepare the second array: input combination
    unlock = processLocker();                                             // compare two arrays
    if (unlock) {                                                         // if they match
      Serial.println("Password correct! You have unlocked the locker.");  // ## do something here ##
      while (true) {};                                                    // end the loop
    }
  }

  // check if user has exhausted their attempts
  if (remaining_attempts <= 0) {
    Serial.println("Maximum attempts reached. Alarm triggered.");
    while (true) {
      alarm();  // trigger alarm indefinitely
    }
  }

  Serial.println();  // debug print
  delay(10);         // how long should it check
}


// function to convert password string into an integer array
void setPasswordArray(String password_string) {
  Serial.print("Password: ");                            // debug print
  if (password_string.length() == MAX_PASSWORD_DIGIT) {  // check if the length of password is valid for 2 DIP switches
    bool all_zeros = true;                               // variable to check if the password is all zeros
    bool all_ones = true;                                // variable to check if the password is all ones

    for (int i = 0; i < MAX_PASSWORD_DIGIT; i++) {  // loop for all characters in a string
      if (password_string[i] == '0') {              // for a particular character
        password_combination[i] = 0;                // add corresponding integer
        all_ones = false;                           // set to false because there is at least one 0
      } else if (password_string[i] == '1') {       // for a particular character
        password_combination[i] = 1;                // add corresponding integer
        all_zeros = false;                          // set to false because there is at least one 1
      }
      Serial.print(password_combination[i]);  // debug print
    }
    Serial.println();  // debug print

    if (all_zeros || all_ones) {  // check if the password is all zeros or all ones
      Serial.println("Password cannot be all 0s or all 1s.");
      while (true) {};  // halt the program
    }
  }
}


// function to read current input combination
void getCurrentInput() {
  Serial.print("Current input: ");  // debug print

  for (int i = 0; i < MAX_PASSWORD_DIGIT; i++) {
    input_combination[i] = !digitalRead(switch_pins[i]);  // store pulldown equivalent button states
    Serial.print(input_combination[i]);                   // debug print
  }
  Serial.println();  // debug print
}


// function to check if the input is the password
bool processLocker() {
  for (int i = 0; i < MAX_PASSWORD_DIGIT; i++) {
    if (input_combination[i] != password_combination[i]) {  // one mismatch --> incorrect input
      remaining_attempts--;                                 // reduce one attempt count
      return false;
    }
  }
  return true;  // no mismatch --> correct password
}


// function to set the alarm on
void alarm() {
  for (int i = 200; i <= 800; i++) {  // define custom frequency range
    tone(buzzer, i);                  // pass each frequency
    delay(5);
  }
}
