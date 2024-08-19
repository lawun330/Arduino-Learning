#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 206
#define SERVOMAX 416
#define USMIN 400
#define USMAX 2400
#define SERVO_FREQ 50

uint8_t servonum = 0;
//int degree=0;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(25497000);  //25497590 the same
  pwm.setPWMFreq(SERVO_FREQ);            //50Hz
  delay(10);
}

void loop() {

  Serial.println(servonum);
  /* for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen);
  }

  delay(500);
//  Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
  */
  // The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior.
  for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
    pwm.writeMicroseconds(servonum, microsec);
  }


  delay(500);
  for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
    pwm.writeMicroseconds(servonum, microsec);
  }
  delay(500);
}


void RunServo() {
  for (int degree = 0; degree == 90; degree++) {
    int angle1 = map(degree, 0, 180, USMIN, USMAX);  //val between USMIN and USMAX
    int angle2 = map(degree, 0, 180, SERVOMIN, SERVOMAX);
    //pwm.setPWM(0, 0, angle2);
    pwm.writeMicroseconds(0, angle1);
  }
}
