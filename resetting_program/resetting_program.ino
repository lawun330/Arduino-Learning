
//NOTE *** reset occurs when pin is LOW

int Reset = 4;

void setup() {  
  oneline_setup();
}
void loop() 
{
  oneline_loop();

}









////////////////////

//reset in programming way

void pro_setup()
{
  digitalWrite(Reset, HIGH);
  delay(200); 
  pinMode(Reset, OUTPUT);     
  Serial.begin(9600);
  Serial.println("How to Reset Arduino Programmatically");
  Serial.println("www.TheEngineeringProjects.com");
  delay(200);
}

void pro_loop()
{
  Serial.println("A");
  delay(1000);               
  Serial.println("B");
  delay(1000);               
  Serial.println("Now we are Resetting Arduino Programmatically");
  Serial.println();
  delay(1000);
  digitalWrite(Reset, LOW);
  Serial.println("Arduino will never reach there.");
}

/////////////////////

//reset in one line

void (*resetFunc)(void) = 0;
 
void oneline_setup() 
{     
  Serial.begin(9600);
  Serial.println("How to Reset Arduino Programmatically");
  Serial.println("www.TheEngineeringProjects.com");
  delay(200);
}

void oneline_loop() 
{
  Serial.println("A");
  delay(1000);               
  Serial.println("B");
  delay(1000);               
  Serial.println("Now we are Resetting Arduino Programmatically");
  Serial.println();
  delay(1000);
  resetFunc();
  Serial.println("Arrduino will never reach there.");
}
/////////////////////

//button and reset

#define button 1

int x=0;
boolean Butt;

void butt_setup()
{
  digitalWrite(Reset,HIGH);
  pinMode(button,INPUT_PULLUP);
  pinMode(Reset,OUTPUT);
}

void butt_loop()
{
  boolean Butt=!digitalRead(button);
  x++;
  Serial.print(Butt);
  Serial.print("\t");
  Serial.println(x);

  if(Butt==1){
    digitalWrite(5,LOW);
    Serial.println("resetting");
  }
}
//////////////////////
