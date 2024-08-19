/* Project: INFRA-RED SIGNALS CONTROLLED CAR
 * ### TX REMOTE SIDE ### 
 * This script sends specified IR signals to the IR-signal receiver.
 * 
 * Components:
 *  + joystick module
 *  + IR-signal transmitter
 * 
 * The position of the joystick determines which signal to send.
 * Signals are sent in the hexadecimal (HEX) form.
 * These signals will be received in the decimal form.
 * 
 * Mappings:
 *  - 0x80BF53AC is the hexadecimal (HEX) equivalent of the decimal 2160022444
 *  - 0x80BF4BB4 is the hexadecimal (HEX) equivalent of the decimal 2160020404
 *  - 0x80BF9966 is the hexadecimal (HEX) equivalent of the decimal 2160040294
 *  - 0x80BF837C is the hexadecimal (HEX) equivalent of the decimal 2160034684
 * 
 * The default signal, 0x70CA9977, does not need to be read at all. There is no mapping for it.
 * Library source: https://github.com/Arduino-IRremote/Arduino-IRremote */


#include <IRremote.h>

int IR_transmitter_pin = 3;  // usually 3 for uno # check gitHub for details
int joystick_x_pin = A0;
int joystick_y_pin = A1;

IRsend irsend;


void setup() {
  Serial.begin(9600);
  irsend.begin();

  pinMode(joystick_x_pin, INPUT);
  pinMode(joystick_y_pin, INPUT);
}


void loop() {
  // map joystick readings to avoid small noises
  int x = map(analogRead(joystick_x_pin), 0, 1023, 0, 10);
  int y = map(analogRead(joystick_y_pin), 0, 1023, 0, 10);
  Serial.println(String(x) + "  " + String(y));  // debug print

  // Define a dead zone to ignore small joystick movements
  const int deadZone = 1;

  // send IR signals based on joystick position
  if (abs(x - 5) > deadZone || abs(y - 5) > deadZone) {
    if (x == 0 && y == 5) {  // joystick up
      irsend.sendNEC(0x80BF53AC, 32);
    } else if (x == 10 && y == 5) {  // joystick down
      irsend.sendNEC(0x80BF4BB4, 32);
    } else if (x == 5 && y == 0) {  // joystick left
      irsend.sendNEC(0x80BF9966, 32);
    } else if (x == 5 && y == 10) {  // joystick right
      irsend.sendNEC(0x80BF837C, 32);
    }
  } else {
    // No significant joystick movement, do not send any signal
    // Comment out the default signal to avoid unnecessary transmissions
    // irsend.sendNEC(0x70CA9977, 32);    // default signal
  }
  delay(500);
}
