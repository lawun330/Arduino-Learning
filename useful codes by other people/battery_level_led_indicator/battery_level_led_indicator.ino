//--------Program developed by R.Girish---------//
int analogInput = A0;

float vout = 0.0;
float vin = 0.0;
float R1 = 100000;
float R2 = 10000;
int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(analogInput, INPUT);
}

void loop() {
  value = analogRead(analogInput);
  Serial.print("analog val = ");
  Serial.print(value);

  vout = (value * 5.0) / 1024;
  Serial.print("\tOutput Voltage = ");
  Serial.print(vout);

  vin = (vout / (R2 / (R1 + R2)) + 0.2);
  Serial.print("\tInput Voltage = ");
  Serial.println(vin);

  delay(2000);
}
//--------Program developed by R.Girish---------//
