/* This script is for a bluetooth-controlled, 2-servo-connected car. 
 * The car is used to participate in the YTU Rolympics 2019.
 * TEAM NAME: TORNEDO
 * MEMBERS: 4 MEMBERS
 *
 * Notes :
    * Here, the left or right turning code, forward or backward whatever is basically the idea of rotating the car.
    * The car will move for "t" milliseconds and stop automatically (for forward and backward) to make better movements.
    * A switch should be soldered with battery wire to prevent unwanted dangers such as battery explosion.
    * A total of 4 PWM digital pins are used: 2 for enable pins; 2 for servos.
    * No motor (wheel) will move in case other data are sent via the bluetooth (like String or float). >>> To change this, go to switch statement.
    * In this script, 'A' refers to left side of the car, and 'B', the right side.
    * Use a single servo if using two servos is unstable.
    * In switch cases, 'T' represents triangle, 'O' - circle, 'X' - cross, and 'S' - square. These are the button symbols of the app.
    * For 'O' and 'T', each case turns the servos to specific direction.
    * Each press of 'T' or 'O' will rotate the servos by 10 degree. >>> To change this, go to switch statement.
 */


#include <SoftwareSerial.h>
#include <Servo.h>

// motor pins // enable pins --> PWM digital pins
#define enA 5
#define in1 3
#define in2 4
#define in3 7
#define in4 8
#define enB 6

// servo pins // PWM digital pins
int servoA_pin = 10;
int servoB_pin = 11;

// define initial degrees for servos
int servoA_position = 0;
int servoB_position = 180;

char command;       // variable to receive bluetooth command
String state = "";  // variable

SoftwareSerial my_bluetooth(12, 13);  // pass the bluetooth pins // (RX,TX)
Servo servoA;
Servo servoB;


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // connect servos
  servoA.attach(servoA_pin);
  servoB.attach(servoB_pin);

  // initialize servos to default degrees
  servoA.write(servoA_position);
  servoB.write(servoB_position);
}


void loop() {
  if (my_bluetooth.available()) {  // if bluetooth is available
    command = my_bluetooth.read();
    Serial.println(command);

    switch (command) {
      case 'F':
        forwardCar(200, 500);  // pass (speed, duration_to_move)
        break;

      case 'B':
        backwardCar(180, 500);
        break;

      case 'L':
        left_forwardCar(80, 180);  // left speed < right speed, to go left
        break;

      case 'R':
        right_forwardCar(180, 80);  // left speed > right speed, to go right
        break;

      case 'X':
        right_backwardCar(80, 180);
        break;

      case 'S':
        left_backwardCar(180, 80);
        break;

      case 'O': servosMode1(10); break;  // move servos 10 degrees

      case 'T': servosMode2(10); break;  // move servos 10 degrees

      default: stopCar();
    }
  }
}

/*******************************************************/

// function for the car to move forward straight for 'time' milliseconds and stop
void forwardCar(int speed, int time) {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(enA, speed);  // analogWrite function is used on PWM digital connection
  analogWrite(enB, speed);  // analogWrite function is used on PWM digital connection
  delay(time);              // move for 'time' milliseconds
  stopCar();                // stop
}


// function for the car to move backward straight for 'time' milliseconds and stop
void backwardCar(int speed, int time) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(enA, speed);  // analogWrite function is used on PWM digital connection
  analogWrite(enB, speed);  // analogWrite function is used on PWM digital connection
  delay(time);              // move for 'time' milliseconds
  stopCar();                // stop
}


// function for the car to move forward to right direction
void right_forwardCar(int enA_speed, int enB_speed) {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(enA, enA_speed);  // analogWrite function is used on PWM digital connection
  analogWrite(enB, enB_speed);  // analogWrite function is used on PWM digital connection
}


// function for the car to move forward to left direction
void left_forwardCar(int enA_speed, int enB_speed) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(enA, enA_speed);  // analogWrite function is used on PWM digital connection
  analogWrite(enB, enB_speed);  // analogWrite function is used on PWM digital connection
}


// function for the car to move backward to right direction // same with left_forwardCar()
void right_backwardCar(int enA_speed, int enB_speed) {
  left_forwardCar(enA_speed, enB_speed);
}


// function for the car to move backward to left direction // same with right_forwardCar()
void left_backwardCar(int enA_speed, int enB_speed) {
  right_forwardCar(enA_speed, enB_speed);
}


// function to stop the car
void stopCar() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

/*******************************************************/

// function to move servos to position 1
void servosMode1(int degree) {
  if (servoA_position >= 180) {
    servoA_position = 180;
  } else {
    servoA.write(servoA_position += degree);
  }
  if (servoB_position <= 0) {
    servoB_position = 0;
  } else {
    servoB.write(servoB_position -= degree);
  }
}


// function to move servos to position 2
void servosMode2(int degree) {
  if (servoA_position <= 0) {
    servoA_position = 0;
  } else {
    servoA.write(servoA_position -= degree);
  }
  if (servoB_position >= 180) {
    servoB_position = 180;
  } else {
    servoB.write(servoB_position += degree);
  }
}

/*******************************************************/
