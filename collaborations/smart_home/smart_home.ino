/* This script is me and my partner's first big project with the Arduino platform.
 
 * ##### Smart Home Automation Project #####
 * TEAM MEMBERS: 2 
 *  - LA WUN NANNDA 
 *  - THIHA
 *
 * This project uses an Arduino Mega to create a smart home system with various sensors and actuators.
 * 
 * Components used:
 * - 3 Servos: Controls mechanical movements for doors and barrier gate
 * - 3 Ultrasonic sensors: Measures distance for doors and barrier gate
 * - Button: Allows manual input for fan
 * - Relay1: Connects to the fan
 * - DHT sensor: Measures temperature and humidity for fire detection
 * - LM35 sensor: Measures temperature for fire detection
 * - Flame sensor: Detects fire for fire detection
 * - Buzzer: Provides audible alerts for fire alarm
 * - Bluetooth HC06: Enables wireless communication for fire alarm, bluetooth commands
 * - 3 LEDs: Provides visual indicators for bluetooth commands
 * - LDR sensor: Measures light intensity for light automation
 * - Relay2: Connects to the light bulb for light automation
 *
 * Procedures:
 * - measureDistance: Measures distance using ultrasonic sensors
 * - autoDoor: Automatically opens/closes a door based on distance
 * - autoBarrierGate: Controls a barrier gate using distance measurements
 * - toggleFan: Toggles a fan using a button
 * - detectFire: Detects fire and heat
 * - fireAlarm: Sends a fire alert via Bluetooth
 * - toggleLED: Toggles LEDs on/off
 * - toggleLEDs: Controls LEDs using Bluetooth commands
 * - autoLight: Automatically turns lights on/off based on room brightness
 * 
 * Pins may vary depending on the connections of the components.
 */

#include <Servo.h>
#include <DHT.h>
#include <SoftwareSerial.h>  // for bluetooth communication

// LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// servos
const int servo1_pin = 5;
const int servo2_pin = 6;
const int servo3_pin = 7;
Servo servo1;
Servo servo2;
Servo servo3;

// bluetooth
const int RX = 8;
const int TX = 9;
SoftwareSerial my_bluetooth(RX, TX);

// ultrasonic
const int echo1 = 10;
const int echo2 = 11;
const int echo3 = 12;
const int trig1 = 13;
const int trig2 = 14;
const int trig3 = 15;

// button
const int button_pin = 16;

// buzzer
const int buzzer_pin = 17;

// fan
const int fan_pin = 18;  // relay connected

// light bulb
const int light_bulb = 19;  // relay connected

// sensors
const int dht_pin = 20;
DHT my_dht(dht_pin, DHT11);
const int LM35_pin = A0;
const int flame_pin = A1;
const int LDR_pin = A2;

// variables
int x = 0;            // state of LED1
int y = 0;            // state of LED2
int z = 0;            // state of LED3
float distance1 = 0;  // Initialize distances
float distance2 = 0;
float distance3 = 0;
const int brightness_threshold = 500;  // under this value, the lights are turned on
const int servo_degree = 90;           // default degree of the servo
const float temp_threshold = 36.0;     // threshold for the temperature
const int flame_threshold = 500;       // threshold for the flame
const float garage_height = 5;         // distance between the ceiling and the floor of the garage
bool fan_state = false;                // to track the fan state


void setup() {
  Serial.begin(9600);        // initialize serial communication
  my_bluetooth.begin(9600);  // initialize bluetooth communication

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(LM35_pin, INPUT);
  pinMode(flame_pin, INPUT);
  pinMode(LDR_pin, INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(fan_pin, OUTPUT);

  // attach the servo to the pin
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);

  // initialize servos to default 90 degrees
  servo1.write(servo_degree);
  servo2.write(servo_degree);
  servo3.write(servo_degree);

  // initialize LEDs to off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // initialize buzzer to no sound
  digitalWrite(buzzer_pin, LOW);

  // initialize fan to off
  digitalWrite(fan_pin, LOW);
}

/******************************************************************************/

// function to measure distance with ultrasonic sensor
void measureDistance(int trig_pin, int echo_pin, float &distance) {  // use pass by reference to change the value of the variable
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  float time = pulseIn(echo_pin, HIGH);
  distance = time * 0.034 / 2;
}


// function to automatically open the door with ultrasonic sensor and 2 servos
void autoDoor() {
  measureDistance(trig1, echo1, distance1);
  Serial.print("Distance from door: ");
  Serial.print(distance1);
  Serial.print(" cm");

  if (distance1 <= 6) {
    // Object detected within 6 cm, open the door
    servo1.write(servo_degree + 90);
    servo2.write(servo_degree - 90);
  } else {
    // No object within 6 cm, close the door
    servo1.write(servo_degree);
    servo2.write(servo_degree);
  }
}


// function to automatically open the barrier gate with 2 ultrasonic sensors and 1 servo
void autoBarrierGate() {
  measureDistance(trig2, echo2, distance2);
  Serial.print("Distance from barrier gate: ");
  Serial.print(distance2);
  Serial.println(" cm");

  measureDistance(trig3, echo3, distance3);
  Serial.print("Distance from the ceiling: ");
  Serial.print(distance3);
  Serial.println(" cm");

  if (distance2 <= 6 and distance3 >= garage_height) {  // if the car is within 6 cm and there is no car in the parking space
    servo3.write(servo_degree + 90);                    // open the barrier gate
  } else if (distance3 < garage_height) {               // if there is a car in the parking space
    servo3.write(servo_degree);                         // close the barrier gate
  }
}

/******************************************************************************/

// function to control a (relay-connected) fan with button
void toggleFan() {
  bool button_state = !digitalRead(button_pin);  // pulldown equivalent
  static bool last_button_state = LOW;           // track the last button state
  static unsigned long last_debounce_time = 0;   // debounce timer
  const unsigned long debounce_delay = 50;       // debounce delay

  if (button_state != last_button_state) {
    last_debounce_time = millis();  // reset the debounce timer
  }

  if ((millis() - last_debounce_time) > debounce_delay) {  // debounce
    if (button_state == HIGH) {                            // detect button press
      fan_state = !fan_state;                              // toggle fan state
      digitalWrite(fan_pin, fan_state ? HIGH : LOW);       // turn on or off the fan
    }
  }

  last_button_state = button_state;  // update last button state
}

/******************************************************************************/

// function to detect fire and heat
void detectFire() {
  float flame = analogRead(flame_pin);
  float LM35temp = analogRead(LM35_pin) * 0.48828;
  float dhttemp = my_dht.readTemperature();

  if (isnan(dhttemp)) {  // check if the DHT sensor reading is valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (LM35temp < 0 || LM35temp > 100) {  // check if the LM35 sensor reading is within a reasonable range
    Serial.println("Failed to read from LM35 sensor!");
    return;
  }

  float avgtemp = (LM35temp + dhttemp) / 2;

  Serial.print("Average temperature: ");
  Serial.print(avgtemp);
  Serial.print("*C flame: ");
  Serial.println(flame);

  if (avgtemp > temp_threshold && flame > flame_threshold) {  // if the heat and flame is detected
    // non-blocking delay
    unsigned long start_time = millis();
    while (millis() - start_time < 1000) {}  // 1 second delay

    if (avgtemp > temp_threshold && flame > flame_threshold) {  // if the heat and flame is still there
      fireAlarm();                                              // it is indeed fire, call the fireAlarm function
    }
  }
}


// function to notify the user that fire is detected using bluetooth
void fireAlarm() {
  tone(buzzer_pin, 1000, 1000);
  my_bluetooth.println("Fire detected in your home!!!");
}

/******************************************************************************/

// function to toggle LEDs
void toggleLED(int ledPin, int &state) {
  digitalWrite(ledPin, state == 0 ? HIGH : LOW);
  state = 1 - state;
}


// function to toggle LEDs with bluetooth commands
void toggleLEDs() {
  if (my_bluetooth.available()) {
    char command = my_bluetooth.read();

    if (command == 'A') {
      toggleLED(led1, x);
    }

    if (command == 'B') {
      toggleLED(led2, y);
    }

    if (command == 'C') {
      toggleLED(led3, z);
    }
  }
}

/******************************************************************************/

// function to automatically turn (relay-connected) light bulb on or off based on the brightness of the room
void autoLight() {
  float brightness = analogRead(LDR_pin);
  Serial.print("ldr value: ");
  Serial.println(brightness);

  if (brightness < brightness_threshold) {  // turn light bulb on in the dark
    digitalWrite(light_bulb, HIGH);
  } else {  // turn light bulb off otherwise
    digitalWrite(light_bulb, LOW);
  }
}

/******************************************************************************/

void loop() {
  // Automatically control the door
  autoDoor();

  // Automatically control the barrier gate
  autoBarrierGate();

  // Control the fan with the button
  toggleFan();

  // Detect fire and heat
  detectFire();

  // Toggle LEDs with Bluetooth commands
  toggleLEDs();

  // Automatically control the light bulb based on room brightness
  autoLight();

  // Add a small delay to avoid overwhelming the loop
  delay(100);
}
