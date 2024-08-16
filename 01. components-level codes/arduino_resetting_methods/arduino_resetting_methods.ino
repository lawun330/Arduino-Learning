/* 
  The reset is triggered when the specified pin is set to LOW. 
  It includes three methods for resetting: 
  - a programming method, 
  - a function pointer method, and 
  - a button-based method.
  The code is adapted from the following link:
  https://www.theengineeringprojects.com/2020/05/how-to-reset-arduino-programmatically.html
*/


int reset_pin = 4;


void setup() {
  pinMode(reset_pin, OUTPUT);
  digitalWrite(reset_pin, HIGH);
  Serial.begin(9600);
  Serial.println("Setup complete");
  delay(200);

  // programmingSetup();      // uncomment to use programming reset
  // functionPointerSetup();  // uncomment to use function pointer reset
  // buttonSetup();           // uncomment to use button reset
}


void loop() {
  // programmingLoop();      // uncomment to use programming reset
  // functionPointerLoop();  // uncomment to use function pointer reset
  // buttonLoop();           // uncomment to use button reset
}

/************************************************************************/
/* Programming Reset: This method sets the reset pin to LOW programmatically to trigger the reset. */

void programmingSetup() {}

void programmingLoop() {
  Serial.println("##some task here##");
  delay(1000);
  Serial.println("Now we are resetting Arduino programmatically");
  Serial.println();
  delay(1000);
  digitalWrite(reset_pin, LOW);  // set the reset pin to LOW to trigger the reset
  Serial.println("Arduino will never reach here.");
}

/************************************************************************/
/* Function Pointer Reset: This method uses a function pointer to reset the Arduino programmatically. */

void (*resetFunc)(void) = 0;  // function pointer to reset the Arduino

void functionPointerSetup() {}

void functionPointerLoop() {
  Serial.println("##some task here##");
  delay(1000);
  Serial.println("Now we are resetting Arduino with function pointer");
  Serial.println();
  delay(1000);
  resetFunc();  // call the function pointer to reset the Arduino
  Serial.println("Arduino will never reach here.");
}

/************************************************************************/
/* Button Reset: This method uses a button to reset the Arduino programmatically. */

#define BUTTON_PIN 5

int counter = 0;
bool buttonState;

void buttonSetup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void buttonLoop() {
  Serial.println(counter);  // print the counter to know that the loop is running
  delay(1000);

  buttonState = !digitalRead(BUTTON_PIN);
  Serial.println(buttonState);  // debugging print

  if (buttonState) {  // if the button is pressed
    Serial.println("Now we are resetting Arduino with button");
    Serial.println();
    delay(1000);
    digitalWrite(reset_pin, LOW);  // set the reset pin to LOW to trigger the reset
    Serial.println("Arduino will never reach here.");
  }
  counter++;
}

/************************************************************************/