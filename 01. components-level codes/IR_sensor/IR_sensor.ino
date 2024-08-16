/* This script illustrates the use of IR sensor.
IR remote is needed for the IR sensor to receive signals.
It can be applied to get IR remote control signals.
Example: get the signal of the volume button on the TV remote. */


#include <IRremote.h>

int RECV_PIN = 6;
IRrecv my_IR_sensor(RECV_PIN);
decode_results result;


void setup() {
  Serial.begin(9600);
  my_IR_sensor.enableIRIn();
  Serial.print("Start!");
}


void loop() {
  if (my_IR_sensor.decode(&result)) {
    Serial.println(result.value, DEC);
    my_IR_sensor.resume();
  }
  delay(100);
}
