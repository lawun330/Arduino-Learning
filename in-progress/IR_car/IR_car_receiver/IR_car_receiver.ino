/* Project: INFRA-RED SIGNALS CONTROLLED CAR
 * ### RX CAR SIDE ###
 * This script receives specified IR signals from the IR-signal transmitter.
 * 
 * Components:
 *  + 2 motors (wheels)
 *  + IR-signal receiver
 * 
 * A particular signal determines which car movement to make.
 * Signals are received in the hexadecimal (HEX) form.
 * These signals were sent in the decimal form.
 *
 * Mappings:
 *  - 2160022444 is the decimal equivalent of the HEX code 0x80BF53AC
 *  - 2160020404 is the decimal equivalent of the HEX code 0x80BF4BB4
 *  - 2160040294 is the decimal equivalent of the HEX code 0x80BF9966
 *  - 2160034684 is the decimal equivalent of the HEX code 0x80BF837C
 *
 * The default signal, 0x70CA9977, does not need to be read at all. There is no mapping for it.
 * Library source: https://github.com/Arduino-IRremote/Arduino-IRremote */


#include <IRremote.h>

int IR_receiver_pin = 2;  // usually 2 for uno # check gitHub for details
int left_wheel_forward_pin = 7;
int left_wheel_backward_pin = 6;
int right_wheel_forward_pin = 5;
int right_wheel_backward_pin = 4;
int delay_time = 500;

IRrecv irrecv(IR_receiver_pin);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(left_wheel_forward_pin, OUTPUT);
  pinMode(left_wheel_backward_pin, OUTPUT);
  pinMode(right_wheel_forward_pin, OUTPUT);
  pinMode(right_wheel_backward_pin, OUTPUT);
}

void loop() {
  // receive IR signals
  if (irrecv.decode(&results)) {
    unsigned long x = results.value;
    irrecv.resume();    // receive the next value
    Serial.println(x);  // debug print

    // stop the car before changing direction
    digitalWrite(left_wheel_forward_pin, LOW);
    digitalWrite(left_wheel_backward_pin, LOW);
    digitalWrite(right_wheel_forward_pin, LOW);
    digitalWrite(right_wheel_backward_pin, LOW);
    delay(delay_time);

    // car movement
    if (x == 2160022444) {                           // forward
      digitalWrite(left_wheel_forward_pin, HIGH);    //
      digitalWrite(right_wheel_forward_pin, HIGH);   //
      delay(delay_time);                             //
    } else if (x == 2160020404) {                    // backward
      digitalWrite(left_wheel_backward_pin, HIGH);   //
      digitalWrite(right_wheel_backward_pin, HIGH);  //
      delay(delay_time);                             //
    } else if (x == 2160040294) {                    // left
      digitalWrite(left_wheel_backward_pin, HIGH);   //
      digitalWrite(right_wheel_forward_pin, HIGH);   //
      delay(delay_time);                             //
    } else if (x == 2160034684) {                    // right
      digitalWrite(left_wheel_forward_pin, HIGH);    //
      digitalWrite(right_wheel_backward_pin, HIGH);  //
      delay(delay_time);                             //
    }                                                // no need for else, as the car is already stopped
  }
}