/* This script rotates the stepper motor step by step in clockwise or counterclockwise direction.
 * Remember that clockwise or counterclockwise direction is determined by the order of the HIGHs and LOWs of in1 to in4.
 * In this script, the HIGHs and LOWs of in1 to in4 in- 
    * acending order --> counterclockwise 
    * decending order --> clockwise
  Pin connections:
    * digital pin 11 10 9 8 - in1 in2 in3 in4 (counterclockwise)
    * digital pin 11 10 9 8 - in4 in3 in2 in1 (clockwise)
  * Note that changing pin connections will change the direction of rotation determined by this script.
*/


#define in1 8
#define in2 9
#define in3 10
#define in4 11

int counter = 1;


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop() {
  stepper(true);
  delay(1);
}


// function to rotate the stepper motor step by step
void stepper(bool clockwise) {
  switch (counter) {
    case 1:
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
      break;

    case 2:
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
      break;

    case 3:
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
      break;

    case 4:
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
      break;

    default:
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
      break;
  }

  // clockwise or counterclockwise
  if (clockwise) {
    counter--;
  } else {
    counter++;
  }

  // reset the counter
  if (counter < 1) {
    counter = 4;
  } else if (counter > 4) {
    counter = 1;
  }
}
