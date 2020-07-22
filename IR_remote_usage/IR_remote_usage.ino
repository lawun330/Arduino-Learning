//to know what the button on remote means with IR reader

#include <IRremote.h>

int RECV_PIN=11;
IRrecv haha(RECV_PIN); 
decode_results result;

void setup() {
Serial.begin(9600);
haha.enableIRIn();
Serial.print("Start!");

}

void loop() {
if (haha.decode(&result)){
  Serial.println(result.value,DEC);
  haha.resume();
  }
  delay(100);
}
