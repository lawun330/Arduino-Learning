/* This script is a proof that we can write pure mathematical functions with Arduino.
It is a simple math game played through the serial input.
There is a timer and a score counter. The game ends when the timer is up. 
Enjoy! */


int fixedTime = 0;
int score = 0;
const int requiredTime = 10;


void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to math game!!");
}


void loop() {
  Serial.println("Press 'S' to start");

  while (Serial.available() == 0) {
    // Wait for user input
  }

  // check if the user pressed 'S'
  if (Serial.available() > 0) {
    char ch = Serial.read();
    Serial.flush();  // clear the buffer
    if (ch == 'S') {
      startGame();
    }
  }
}


// function to start the game
void startGame() {
  score = 0;  // reset the score
  fixedTime = millis() / 1000;

  // main game loop
  while (true) {
    int currentTime = millis() / 1000;
    int elapsedTime = currentTime - fixedTime;

    // if the timer is up during answering
    if (elapsedTime >= requiredTime) {
      endGame();
      break;
    }

    // ask the question
    int randomVal = random(2, 100);
    Serial.print("Find the square of ");
    Serial.println(randomVal);

    // compute the correct answer
    int correctAnswer = randomVal * randomVal;

    // wait for the player's answer
    while (Serial.available() == 0) {
      currentTime = millis() / 1000;
      elapsedTime = currentTime - fixedTime;

      // if the timer is up during waiting
      if (elapsedTime >= requiredTime) {
        endGame();
        return;  // exit the function to avoid nested breaks
      }
    }

    // read the player's answer
    int typedNumber = Serial.parseInt();
    Serial.flush();  // clear the buffer
    Serial.println();
    Serial.print("You typed: ");
    Serial.println(typedNumber);

    // check and add the score for correct answers
    if (typedNumber == correctAnswer) {
      score++;
      Serial.println("Correct!");
    } else {
      Serial.println("Wrong!");
    }
    Serial.println();
  }
}


// function to display the final score and ask the user to start the game again
void endGame() {
  Serial.println();
  Serial.print("Time's up! YOUR SCORE IS ");
  Serial.println(score);
}
