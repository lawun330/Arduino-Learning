#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  //ce,csn

const byte address[6] = "3rr0r";

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  int potVal = analogRead(A0);
  int angleV = map(potVal, 0, 1023, 0, 180);
  Serial.println(angleV);
  radio.write(&angleV, sizeof(angleV));
  delay(10);
}
