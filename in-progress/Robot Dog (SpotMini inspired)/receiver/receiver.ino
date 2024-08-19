#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servo;
RF24 radio(7, 8);  //ce,csn

const byte address[6] = "3rr0r";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  servo.attach(5);
  radio.startListening();
}

void loop() {


  if (radio.available()) {
    while (radio.available()) {
      int angle = 0;
      radio.read(&angle, sizeof(angle));
      Serial.println(angle);
      servo.write(angle);
    }
  }
}
