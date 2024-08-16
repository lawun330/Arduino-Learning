/* This script is used to control things using voice commands.
You will need to download the voice control application on your phone to send data to the Arduino via bluetooth.
The voice commands are converted to lower case and then compared to the known commands.
If a command is matched, the corresponding thing is turned on or off. 
Here, that things are the LEDs. */


#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(10, 11);  // pass the bluetooth pins
String voice_command;                 // variable to hold the string-equivalent voice command

int LED1 = 3;
int LED2 = 4;
int LED3 = 5;


void setup() {
  Serial.begin(9600);        // initialize the serial communication
  my_bluetooth.begin(9600);  // initialize the bluetooth communication
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}


void loop() {
  while (my_bluetooth.available()) {  // check if there is an available byte to read
    delay(10);                        // delay added to make thing stable # do not delete this line
    char c = my_bluetooth.read();
    voice_command += c;  // build the string by adding each character
  }

  if (voice_command.length() > 0) {  // if the command is ready
    voice_command.toLowerCase();     // convert the string to lowercase
    Serial.println(voice_command);

    if (voice_command == "open" or voice_command == "oban") {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      delay(100);
    } else if (voice_command == "mingalaba") {
      digitalWrite(LED1, HIGH);
      delay(100);
    } else if (voice_command == "kk" or voice_command == "gay gay" or voice_command == "jk") {
      digitalWrite(LED2, HIGH);
      delay(100);
    } else if (voice_command == "saw you" or voice_command == "so you" or voice_command == "solu" or voice_command == "soju") {
      digitalWrite(LED3, HIGH);
      delay(100);
    } else if (voice_command == "shut down" or voice_command == "shirt down" or voice_command == "shirt doll") {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      delay(100);
    }
  }
  voice_command = "";  // reset the voice string
}
