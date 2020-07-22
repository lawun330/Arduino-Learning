//temp indicator with servo and led along with temperature sensor
#include "Servo.h"
#include <DHT.h>

Servo pointer;
DHT dht(7,DHT11);

float AVGvalue;
int outputval;

int ledG=3;
int ledB=4;
int ledR=6;
int buzz=5;
int butt=2;


void setup() {
  
 Serial.begin(9600); 
 dht.begin();
 pointer.attach(10);
 pinMode(butt,INPUT_PULLUP);
 pinMode(ledR,OUTPUT);
 pinMode(ledB,OUTPUT);
 pinMode(ledG,OUTPUT);
 pinMode(buzz,OUTPUT);
 Serial.println("Welcome!!");
 Serial.println("Press the button to start");
 delay(1000);
}

void loop() {

boolean butt=!digitalRead(2);

while (butt==1){
  
delay(2000);  //dht needs 2s to read temperature

float dhttemp = dht.readTemperature();  //dht starts reading
Serial.print("DHT temp: ");
Serial.print(dhttemp);

float LMtemp=analogRead(A0);  // lm35 temp sensor starts reading
LMtemp=LMtemp*0.48828;
Serial.print(" *C  LM35 temp: ");
Serial.print(LMtemp);

AVGvalue=(dhttemp+LMtemp)/2;    //average temp value
Serial.print(" *C  Average value: ");
Serial.print(AVGvalue);
Serial.println(" *C");

outputval= map(AVGvalue,25,45,180,8);
pointer.write(outputval);

if (AVGvalue>=40){
 digitalWrite(ledR,HIGH);
 digitalWrite(ledB,LOW);
 digitalWrite(ledG,LOW);
 digitalWrite(buzz,HIGH);
 }
 
else if (AVGvalue<40 && AVGvalue >30){
 digitalWrite(ledB,HIGH);
 digitalWrite(ledG,LOW);
 digitalWrite(ledR,LOW);
 digitalWrite(buzz,LOW);
 }

else if (AVGvalue<=30){
 digitalWrite(ledG,HIGH);
 digitalWrite(ledR,LOW);
 digitalWrite(ledB,LOW);
 digitalWrite(buzz,LOW);
 }
 break;
 }
 
 if (butt==0){
 digitalWrite(ledG,LOW);
 digitalWrite(ledR,LOW);
 digitalWrite(ledB,LOW);
 digitalWrite(buzz,LOW);
 Serial.println("The button is not being pressed");
 delay(1000);
 }
 }
