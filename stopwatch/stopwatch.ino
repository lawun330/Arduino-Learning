//like a real stopwatch, you can start, pause, reset and close as you want
//use - 4 channels 7 segment display, 2 buttons and a buzzer


#include <TimerOne.h>
// from left to right in upper row- D1,A,F,D2,D3,B
// from left to right in lower row- E,D,deci,C,G,D4
//common grounds are d1 to d4 

int Up=6;         //also called A  
int Down=12;      //also called D
int UpL=5;        //also called F
int DownL=13;     //also called E
int UpR=2;        //also called B
int DownR=10;     //also called C
int Mid=9;        //also called G
int decimal=11;   //also called DP
int butt=1;
int buzz=A0;

#define Secbutton 0
#define D1 7   //thousand digit
#define D2 4   //hundred digit
#define D3 3   //ten digit
#define D4 8   //single digit

int s=-1; int t=0; int h=0; int T=0; int x=0;
 
void setup() {Serial.begin(9600);
 for(int pin=2;pin<14;pin++){
 pinMode(pin,OUTPUT);}
 pinMode(buzz,OUTPUT);
 pinMode(butt,INPUT_PULLUP);
 pinMode(Secbutton,INPUT_PULLUP);}

/****************************/

//here, HIGH makes LED off //LOW makes LED on //It is reversed
void zero(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,0);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,1);}

void one(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,1);
digitalWrite(Down  ,1);
digitalWrite(UpL   ,1);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,1);}

void two(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,1);
digitalWrite(DownL ,0);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,1);
digitalWrite(Mid   ,0);}

void three(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,1);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void four(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,1);
digitalWrite(Down  ,1);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void five(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,1);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void six(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,0);
digitalWrite(UpR   ,1);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void seven(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,1);
digitalWrite(UpL   ,1);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,1);}

void eight(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,0);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void nine(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,0);
digitalWrite(Down  ,0);
digitalWrite(UpL   ,0);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,0);
digitalWrite(DownR ,0);
digitalWrite(Mid   ,0);}

void Off(){
digitalWrite(decimal, 1);
digitalWrite(Up    ,1);
digitalWrite(Down  ,1);
digitalWrite(UpL   ,1);
digitalWrite(DownL ,1);
digitalWrite(UpR   ,1);
digitalWrite(DownR ,1);
digitalWrite(Mid   ,1);}

void buzzOn(){digitalWrite(buzz,HIGH); delay(2000);}
void buzzOff(){digitalWrite(buzz,LOW); delay(0);}

/*********************************************************/

void start(){ 
//starts counting
//the attached function will be executed again after custom delay
 Timer1.initialize(1000000);   //customize the delay (in microseconds)  //1s now
 Timer1.attachInterrupt(add);  //attach the (function) for customized delay
 }

void ledOn(int k){
 
  digitalWrite(D1,LOW);  //off all LEDs
  digitalWrite(D2,LOW);  
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  
switch(k){
 default: digitalWrite(D4,HIGH); break; //turn on the custom digit
  case 1: digitalWrite(D1,HIGH); break;
  case 2: digitalWrite(D2,HIGH); break;
  case 3: digitalWrite(D3,HIGH); break;
  }}
  
void add(){

s++;                  //add counter every 1s
if (s==10){           // s for single-digit   //reset when s= 10
  s=0;
  t++;
if (t==10){           // t for ten-digit
  t=0;
  h++;
if (h==10){           // h for hundred-digit
  T++;
  h=0;
if (T==10){           // T for thousand-digit
  T=0;
}}}}

int realSeconds= (T*1000)+(h*100)+(t*10)+(s);       //sums up to get real time  //function starts from 1
int quotient=(realSeconds/60);                      //divided by 60, then take the natural number
int remainder=realSeconds-(60*quotient);            //difference with real time to get remainder

if(remainder==0){                                   //if divisible by 60,buzzer beeps //an alarm for every minute passed
  if (realSeconds>0){buzzOn(); buzzOff();}}
}

void Display(int y){
  switch(y){                            //for displaying numbers
    default: zero();  break;         
    case 1 : one();   break;
    case 2 : two();   break;
    case 3 : three(); break;
    case 4 : four();  break;
    case 5 : five();  break;
    case 6 : six();   break;
    case 7 : seven(); break;
    case 8 : eight(); break;
    case 9 : nine();  break;}}
    
/**************************************/
void displaying(){
Off();
ledOn(4);
Display(s);
delay(5);

Off();
ledOn(3);
Display(t);
delay(5);

Off();
ledOn(2);
Display(h);
delay(5);

Off();
ledOn(1);
Display(T);
delay(5);
}
/******************************************/
void regular(){

displaying();
start();                     //starts counting  
}

void pause(){

buzzOff();
Timer1.detachInterrupt();
displaying();
}

void reset(){

digitalWrite(D1 ,HIGH);
digitalWrite(D2 ,HIGH);
digitalWrite(D3 ,HIGH);
digitalWrite(D4 ,HIGH);
Display(0);
}

void stopAll(){               //close everything
Off();
buzzOff();                    
Timer1.detachInterrupt();   
s=-1; t=0; h=0; T=0;}

/***************************/

void loop() {

boolean butt=!digitalRead(1);
delay(500);

while (butt==HIGH){                            //press 1 to start

main :
boolean butt=!digitalRead(1);
boolean butt2=!digitalRead(0);

if (butt==LOW and butt2==LOW and x==0){        //keep running without any press
regular();}

while(butt==LOW and butt2==HIGH){              //press 2 to pause
  x=1;

while(x==1){ 
  pause();
  boolean butt=!digitalRead(1);

if(butt==HIGH ){butt=LOW; butt2=LOW; x=0;      //press 1 to resume
goto main;}

}}

if (butt==HIGH and butt2==HIGH){      //press both to stop
reset();
delay(1000);
stopAll();
return loop;}}

if (butt==LOW){                       //It won't start until first press //for never pressing
  stopAll();
  }
}
