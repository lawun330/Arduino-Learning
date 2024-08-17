/* This script uses an infrared (IR) transmitter to send signals based on the position of a joystick.
The infrared receiver reads the signals and displays them on the serial monitor. 
Library source: https://github.com/Arduino-IRremote/Arduino-IRremote */


#include <IRremote.h>
IRsend IRSender;

int joystick_x = A0;
int joystick_y = A1;
int joystick_button = 4;
int IR_TRANSMITTER_LED = 13;
int IR_RECEIVER_LED = 2;


void setup() {
  Serial.begin(9600);
  pinMode(IR_TRANSMITTER_LED, OUTPUT);
  pinMode(IR_RECEIVER_LED, INPUT);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
  pinMode(joystick_button, INPUT_PULLUP);
  
  IRSender.begin();
  IrReceiver.begin(IR_RECEIVER_LED);
}


void loop() {
  int x = map(analogRead(joystick_x), 0, 1023, 0, 10);
  int y = map(analogRead(joystick_y), 0, 1023, 0, 10);
  bool button_state = !digitalRead(joystick_button);  // pulldown equivalent
  Serial.print(String(x) + "  " + String(y) + "  " + String(button_state) + "\n");

  // send IR signals with HEX codes
  if (x == 5 && y == 0) {  // joystick up
    IRSender.sendNEC(0x80BF53AC, 32);
  } else if (x == 5 && y == 10) {  // joystick down
    IRSender.sendNEC(0x80BF4BB4, 32);
  } else if (x == 0 && y == 5) {  // joystick left
    IRSender.sendNEC(0x80BF9966, 32);
  } else if (x == 10 && y == 5) {  // joystick right
    IRSender.sendNEC(0x80BF837C, 32);
  } else {  // joystick center
    IRSender.sendNEC(0x70CA9977, 32);
  }

  if (button_state == 1) {  // joystick button pressed
    IRSender.sendNEC(0x80BF9966, 32);
  }
  delay(500);

  // receive IR signals
  if (IrReceiver.decode()) {
    Serial.print("Received IR signal: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();  // receive the next value
  }

}
