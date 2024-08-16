/* This script is used to control a car using voice commands.
You will need to download the voice control application on your phone to send data to the Arduino via bluetooth.
The voice commands are converted to lower case and then compared to the known commands.
If a command is matched, the corresponding action takes place. */


#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(10, 11);  // pass the bluetooth pins
String voice_command;                 // variable to hold the string-equivalent voice command

int left_wheel_forward_pin = 7;
int left_wheel_backward_pin = 6;
int right_wheel_forward_pin = 5;
int right_wheel_backward_pin = 4;


void setup() {
  Serial.begin(9600);        // initialize the serial communication
  my_bluetooth.begin(9600);  // initialize the bluetooth communication

  pinMode(left_wheel_forward_pin, OUTPUT);
  pinMode(left_wheel_backward_pin, OUTPUT);
  pinMode(right_wheel_forward_pin, OUTPUT);
  pinMode(right_wheel_backward_pin, OUTPUT);
}


void loop() {
  while (my_bluetooth.available()) {  // check if there is an available byte to read
    delay(10);                        // delay added to make thing stable # do not delete this line
    char c = my_bluetooth.read();
    voice_command += c;  // build the string by adding each character - "forward", "reverse", "left" and "right"
  }

  // stop all motors before changing direction
  digitalWrite(left_wheel_forward_pin, LOW);
  digitalWrite(left_wheel_backward_pin, LOW);
  digitalWrite(right_wheel_forward_pin, LOW);
  digitalWrite(right_wheel_backward_pin, LOW);

  if (voice_command.length() > 0) {  // if the command is ready
    voice_command.toLowerCase();     // convert the string to lowercase
    Serial.println(voice_command);

    if (voice_command == "forward") {
      digitalWrite(left_wheel_forward_pin, HIGH);
      digitalWrite(right_wheel_forward_pin, HIGH);
    } else if (voice_command == "backward") {
      digitalWrite(left_wheel_backward_pin, HIGH);
      digitalWrite(right_wheel_backward_pin, HIGH);
    } else if (voice_command == "left") {
      digitalWrite(left_wheel_backward_pin, HIGH);
      digitalWrite(right_wheel_forward_pin, HIGH);
    } else if (voice_command == "right") {
      digitalWrite(left_wheel_forward_pin, HIGH);
      digitalWrite(right_wheel_backward_pin, HIGH);
    } else {
      digitalWrite(left_wheel_forward_pin, LOW);
      digitalWrite(left_wheel_backward_pin, LOW);
      digitalWrite(right_wheel_forward_pin, LOW);
      digitalWrite(right_wheel_backward_pin, LOW);
    }
  }
  voice_command = "";  // reset the voice string
}
