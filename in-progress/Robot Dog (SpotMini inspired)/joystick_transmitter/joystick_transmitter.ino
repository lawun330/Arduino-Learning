#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); //ce,csn

const byte address[6] = "3rr0r";
int Array[2];
bool butt;


////////////////////////////////////////


void setup() {
  Serial.begin(9600);

  //joystick input
  pinMode(A3,INPUT);
  pinMode(A2,INPUT);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


////////////////////////////////////////


void loop() {
  
//  joystick();
int c=2;
radio.write(&c,sizeof(c));
Serial.println(c);
}

////////////////////////////////


void joystick(){
  
  Array[0]=analogRead(A3);
  Array[1]=analogRead(A2);
  
   radio.write(&Array,sizeof(Array));
   
   Serial.print(Array[0]);
   Serial.print("\t"); 
   Serial.println(Array[1]);

  delay(40);
  
  }


///////////////////////////////////
