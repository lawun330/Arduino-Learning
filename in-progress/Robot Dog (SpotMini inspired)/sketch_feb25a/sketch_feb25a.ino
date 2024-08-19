#include <Servo.h>

Servo servo[12];

//coeffient - 98/90, 104/90, 1, 95/90, 104/90, 1, 37/45, 105/90, 1, 95/90, 97/90, 1

const float imdeg[12] = { 120, 105, 90, 60, 75, 90, 120, 105, 90, 60, 75, 90 };
const float coeffient[12] = { 1.0889, 1.1556, 1, 1.0556, 1.1556, 1, 0.8222, 1.1667, 1, 1.0556, 1.0778, 1 };
const float offset[12] = { -10, -16, -4, 0, -14, 0, 34, -7.5, 2, 0, -5.5, 0 };
int servodeg[12];
//float newimdeg[12];
const float Fwalk1[12] = { 109.3777, 99.6888, 90, 60, 75, 90, 120, 105, 90, 70.6222, 80.3111, 90 };
const float Fwalk2[12] = { 112.1352, 111.4833, 90, 60, 75, 90, 120, 105, 90, 67.8671, 68.5166, 90 };
const float Fwalk3[12] = { 123.0247, 116.3388, 90, 60, 75, 90, 120, 105, 90, 56.9753, 63.6612, 90 };

const float Swalk1[12] = { 120, 105, 90, 103.3535, 97.9578, 90, 76.6465, 82.0422, 90, 60, 75, 90 };
const float Swalk2[12] = { 120, 105, 90, 112.1343, 111.4884, 90, 67.8657, 68.5116, 90, 60, 75, 90 };
const float Swalk3[12] = { 120, 105, 90, 123.02, 116.3378, 90, 56.98, 63.6622, 90, 60, 75, 90 };


void getDegree0() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((imdeg[i] * coeffient[i]) + offset[i]); }
}
void getDegree1() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Fwalk1[i] * coeffient[i]) + offset[i]); }
}
void getDegree2() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Fwalk2[i] * coeffient[i]) + offset[i]); }
}
void getDegree3() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Fwalk3[i] * coeffient[i]) + offset[i]); }
}
void getDegree4() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Swalk3[i] * coeffient[i]) + offset[i]); }
}
void getDegree5() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Swalk3[i] * coeffient[i]) + offset[i]); }
}
void getDegree6() {
  for (int i = 0; i < 12; i++) { servodeg[i] = (int)((Swalk3[i] * coeffient[i]) + offset[i]); }
}
//void runServos(float olddeg[], float newdeg[]) {
//  float temp[12];
//  float dA[12];
//  for(int i =0; i<12; i++) {
//    dA[i] = (newdeg[i]-olddeg[i])/10;
//  }
//  for(int i =0; i<12; i++) {
//    temp[i] = olddeg[i]+dA[i];
//    servo[i].write(temp[i]);
//  }
//}

void setup() {
  getDegree0();

  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  //Serial.begin(9600); //Serial.println(servodeg[i]);
  //  Serial.println(imdeg[6]);
  //  Serial.println(coeffient[6]);
  //  Serial.println(offset[6]);
  //  Serial.println(servodeg[6]); //132.664
  //  runServos(imdeg, walk1);
  //  runServos(walk1, walk2);
  //  runServos(walk2, walk3);
}

void loop() {
  moveServos();
}

void moveServos() {
  getDegree1();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  getDegree2();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  delay(500);

  getDegree3();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  delay(500);

  getDegree4();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  delay(500);

  getDegree5();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  delay(500);

  getDegree6();
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 1);
    servo[i].write(servodeg[i]);
  }
  delay(500);
}
