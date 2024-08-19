/* 
  This program is used to control the car using the bluetooth module HC-06 and the OpenCV library.
  The car is controlled by sending the X, Y and Area values to the car.
  The X, Y values are the coordinates of the object in the image.
  The Area value is the area of the object in the image.
*/

#include <SoftwareSerial.h>

SoftwareSerial my_bluetooth(2, 3);  // RX, TX

// global variables
String bluetoothRead;
unsigned short x, y, area;
unsigned short strLength;

// motor pins
int pwmMotorA = 11;
int pwmMotorB = 10;
int leftMotorA = 9;
int leftMotorB = 8;
int rightMotorA = 7;
int rightMotorB = 6;

// motor speed
int motorSpeed = 140;


void setup() {
  // open serial communications and wait for port to open:
  Serial.begin(9600);

  // set the baud rate of (HC-06) Bluetooth module
  my_bluetooth.begin(9600);

  pinMode(pwmMotorA, OUTPUT);
  pinMode(pwmMotorB, OUTPUT);
  pinMode(leftMotorA, OUTPUT);
  pinMode(leftMotorB, OUTPUT);
  pinMode(rightMotorA, OUTPUT);
  pinMode(rightMotorB, OUTPUT);
  analogWrite(pwmMotorA, motorSpeed);
  analogWrite(pwmMotorB, motorSpeed);
}


void loop() {
  register byte ndx = 0;   // register is used to store the index of the array
  char commandbuffer[50];  // character array to store the data from the bluetooth

  if (my_bluetooth.available() > 0) {
    delay(10);
    while (my_bluetooth.available() && ndx < 50) {  // while there is data available in the bluetooth and the index is less than 50
      commandbuffer[ndx++] = my_bluetooth.read();   // read the data from the bluetooth and store it in the array
    }

    commandbuffer[ndx] = '\0';             // add a null terminator to the end of the array
    bluetoothRead = (char*)commandbuffer;  // convert the array to a string
    strLength = bluetoothRead.length();    // get the length of the string
    Serial.println(bluetoothRead);

    if (bluetoothRead.substring(0, 1).equals("X")) {  // if the first character of the string is "X"
      uint8_t pos, i = 1;                             // initialize the position and index

      while (bluetoothRead.substring(i, i + 1) != ("Y")) {  // while the second character of the string is not "Y"
        i++;                                                // increment the index
      }

      x = bluetoothRead.substring(1, i).toInt();  // get the value of X from the string
      Serial.print("X: ");
      Serial.println(x);

      pos = i + 1;                                          // get the position of the next character
      while (bluetoothRead.substring(i, i + 1) != ("A")) {  // while the third character of the string is not "A"
        i++;
      }

      y = bluetoothRead.substring(pos, i).toInt();  // get the value of Y from the string
      Serial.print("Y: ");
      Serial.println(y);

      area = bluetoothRead.substring(i + 1, strLength).toInt();  // get the value of Area from the string
      Serial.print("Area: ");
      Serial.println(area);

      if (x < 750) {
        Serial.println("Left");
        moveLeft();
      } else if (x > 1100) {
        Serial.println("Right");
        moveRight();
      } else if (x >= 750 && x <= 1100) {
        if (area < 150) {
          Serial.println("Forward");
          moveForward();
        } else if (area > 250) {
          Serial.println("Backward");
          moveBackward();
        } else if (area >= 150 && area <= 250) {
          Serial.println("Stop");
          stopCar();
        }
      }
    }
  }
  // all data has been sent, and the buffer is empty.
  Serial.flush();
}


// function to move the car left
void moveLeft() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);
  Serial.println("Left");
  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}


// function to move the car right
void moveRight() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);
  Serial.println("Right");
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}


// function to move the car forward
void moveForward() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);
  Serial.println("Forward");
  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}


// function to move the car backward
void moveBackward() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);
  Serial.println("BAckward");
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}


// function to stop the car
void stopCar() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, LOW);
  Serial.println("STOP");
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, LOW);
}
