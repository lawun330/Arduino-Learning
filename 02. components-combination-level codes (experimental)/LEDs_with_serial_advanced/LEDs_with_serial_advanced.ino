/* This script controls LEDs with a serial monitor input.
A user gives two inputs: the color of the LED and the duration it should light up.
Unique features in this script- String input, timeout, ternary operator, and float conversion.*/

int redLED = 2;
int yellowLED = 3;
int greenLED = 4;


void setup() {
  Serial.begin(9600);
  Serial.println("Welcome!! :D ");
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}


void loop() {
  Serial.println("Press 's' to start :) , 'q' to quit :( ");
  delay(5000);

  if (Serial.available()) {

    char input = Serial.read();  // read character
    Serial.println(input);

    if (input == 's') {  // do things
      Serial.println("Type 'r' for red, 'y' for yellow, 'g' for green:");

      // wait for input with a timeout of 10 seconds
      unsigned long startTime = millis();
      while (!Serial.available() && millis() - startTime < 10000) {}

      if (Serial.available()) {
        char LED_option = Serial.read();  // read character
        Serial.println(LED_option);

        if (LED_option == 'r' || LED_option == 'y' || LED_option == 'g') {
          Serial.println("How long should the LED light up? (in seconds)");

          // wait for input with a timeout of 20 seconds
          while (!Serial.available() && millis() - startTime < 20000) {}

          if (Serial.available()) {
            String durationStr = Serial.readStringUntil('\n');  // read string until newline
            float duration = durationStr.toFloat();             // convert string to float
            Serial.println(duration);

            // ternary operator to determine the LED pin
            int ledPin = (LED_option == 'r') ? redLED : (LED_option == 'y') ? yellowLED
                                                                            : greenLED;

            // control the chosen LED
            controlLED(ledPin, duration);
          } else {  // no duration input
            Serial.println("Timeout waiting for duration input.");
          }
        } else {  // invalid LED input
          Serial.println("Invalid LED option.");
        }
      } else {  // no LED option input
        Serial.println("Timeout waiting for LED option.");
      }
      
    } else if (input == 'q') {  // do nothing
      Serial.println("Thank you for using this, have a nice day!");
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
    }
  }
}


// function to control the LED for a certain duration
void controlLED(int led_pin, float duration) {
  digitalWrite(led_pin, HIGH);
  delay(duration * 1000);
  digitalWrite(led_pin, LOW);
  Serial.println("Your LED lights up for " + String(duration) + " seconds.");
}
