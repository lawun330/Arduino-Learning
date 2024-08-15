/* This script detects an object with the ultrasonic sensor (usually HCSR04) and notify the owner via the bluetooth. 
This functionality can be added to the car's back to park safely. */


#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(10, 11);  // pass bluetooth pins

int echo = 6;    // ultrasonic sensor pins
int trig = 7;    // ultrasonic sensor pins
int buzzer = 5;  // buzzer connected to PWM digital pin

int distance;
int alarming_distance_in_cm = 10;


void setup() {
  Serial.begin(9600);        // initiate serial communication
  my_bluetooth.begin(9600);  // initiate bluetooth communication
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(buzzer, OUTPUT);
}


void loop() {
  // no alarm -> no sound
  noTone(buzzer);

  // produce ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // receive ultrasonic
  float duration = pulseIn(echo, HIGH);

  // process data
  distance = duration * 0.034 / 2;  // convert into centimeter
  Serial.print(distance);
  Serial.println(" cm");

  // alarm scenario
  if (distance < alarming_distance_in_cm) {
    alarm();
  }
}


// function to notify
void alarm() {
  // send data
  if (my_bluetooth.available()) {  // check if bluetooth is available to connect
    my_bluetooth.print("Something is near me at ");
    my_bluetooth.print(distance);
    my_bluetooth.println(" cm");
  }

  // sound alarm
  for (int i = 800; i <= 1500; i++) {  // frequency range
    tone(buzzer, i);
    delay(1);
  }
  for (int i = 1500; i >= 600; i--) {  // frequency range
    tone(buzzer, i);
    delay(1);
  }
}
