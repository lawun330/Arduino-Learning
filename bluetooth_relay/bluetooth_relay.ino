//open the light bulb with bluetooth through relay

#include <SoftwareSerial.h>

SoftwareSerial bt(5,6);
int light=7;

void setup() 
  {
    bt.begin(9600);
    pinMode(light,OUTPUT);
  }

void loop() 
  {
    char a=bt.read();
    if (a=='A')
      {
        digitalWrite(light,HIGH);
      }
    else if (a=='B')
      {
        digitalWrite(light,LOW);
      }
      
  }
