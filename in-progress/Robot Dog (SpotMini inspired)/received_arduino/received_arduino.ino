#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//radio
RF24 radio(7, 8);
const byte address[6] = "3rr0r";
int x_axis, y_axis;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
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

//x,y,0-470,550-1023  470-550 is calm

/**********************************************/
void servoTest() {
  int angle = map(x_axis, 0, 1023, 0, 180);
}
