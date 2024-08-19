#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servo[12];
RF24 radio(7, 8);

//rewrite the imdeg into any desired leg degrees
float imdeg[12] = { 120, 105, 90, 60, 75, 90, 120, 105, 90, 60, 75, 90 };
const float coeffient[12] = { 1.0889, 1.1556, 1, 1.0556, 1.1556, 1, 0.8222, 1.1667, 1, 1.0556, 1.0778, 1 };
const float offset[12] = { -16, -16, -4, 0, -14, 0, 34, -7.5, 2, 0, -5.5, 0 };
const byte address[6] = "3rr0r";

int x_axis, y_axis;
int servodeg[12];

void setup() {
  Serial.begin(9600);
  Serial.println("Initilized...");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  getDegree();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  Serial.println("SETUP DONE");
}

void loop() {

  joystick_input();
}

////////////////////////////////

void joystick_input() {

  if (radio.available()) {
    int Array[2];
    radio.read(Array, sizeof(Array));
    x_axis = Array[0];
    y_axis = Array[1];
    Serial.print(x_axis);
    Serial.print("\t");
    Serial.println(y_axis);
  }
}

/////////////////////////////////

void getDegree() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((imdeg[i] * coeffient[i]) + offset[i]); }
}

/////////////////////////////////

void joystick_output() {
  //right
  if (x_axis < 470) {

  }

  //left
  else if (x_axis > 550) {
  }

  //forward
  if (y_axis < 470) {

  }

  //backward
  else if (y_axis > 550) {
  }
}

//x,y,0-470,550-1023  470-550 is calm

/**********************************************/
void servoTest() {
  int angle = map(x_axis, 0, 1023, 0, 180);
}
