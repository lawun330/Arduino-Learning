/* This script illustrates the use of the XY joystick module */


int x_axis_pin = A1;
int y_axis_pin = A0;
int joystick_button_pin = 8;


void setup() {
  Serial.begin(9600);
  pinMode(x_axis_pin, INPUT);
  pinMode(y_axis_pin, INPUT);
  pinMode(joystick_button_pin, INPUT);
}


void loop() {
  int x_axis = analogRead(x_axis_pin);
  int y_axis = analogRead(y_axis_pin);
  bool button_state = !digitalRead(joystick_button_pin);  // joystick click (button) is similar to input_pullup (add ! for reverse)
  Serial.print(x_axis);
  Serial.print("  ");
  Serial.print(y_axis);
  Serial.print("  ");
  if (button_state) {
    Serial.println("TRUE");
  } else {
    Serial.println("FALSE");
  }
}
