void setup() { 
 Serial.begin(9600);
 
 pinMode(12,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(10,OUTPUT); pinMode(13,OUTPUT);
 
}

void loop() {digitalWrite(13,1);
 digitalWrite(12,1);
 digitalWrite(11,0);
 analogWrite(10,255);

 delay(2000);

//  digitalWrite(4,HIGH);
// digitalWrite(3,0);
// analogWrite(2,255);

// deulay(2000);

}
