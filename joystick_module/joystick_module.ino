//joystick click (button) is like input_pullup system (add ! for reverse)
//joystick module usage sketch

int x_axis;
int y_axis;
bool butt;

void setup() {
Serial.begin(9600);
}

void loop() {
  x_axis=analogRead(A1);
  y_axis=analogRead(A0);
  butt=!digitalRead(8);
Serial.print(x_axis);
Serial.print("  ");
Serial.print(y_axis);
Serial.print("  ");
if (butt){
Serial.println("TRUE");
}
else{
  Serial.println("FALSE");
}
}
