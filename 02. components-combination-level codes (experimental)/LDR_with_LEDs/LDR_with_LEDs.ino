/* This script demonstrates the use of Light Dependent Resistor (LDR) with LEDs. 
Based on a specific resistance value of LDR, it outputs a specific LEDs pattern. */


#define LDR_PIN A0

int LED_1 = 5;
int LED_2 = 7;


void setup() {
  Serial.begin(9600);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}


void loop() {
  float ldr = analogRead(LDR_PIN);  // read LDR value
  Serial.println(ldr);
  delay(500);

  if (ldr > 800) {  // turn LEDs off, not in the dark space
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    Serial.println("No LEDs.");
  }

  else if (ldr <= 800 && ldr > 600) {  // turn one LED on, in the dark space
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    Serial.println("1 LEDs.");
  }

  else if (ldr < 600) {  // turn two LEDs on, in the darker space
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    Serial.println("2 LEDs.");
  }
}
