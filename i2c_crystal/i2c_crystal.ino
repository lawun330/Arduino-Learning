//smart chat between bluetooth and serial displayed on lcd i2c
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>


SoftwareSerial bluetooth(3,2);
LiquidCrystal_I2C lcd(0x38,16,2);

int row=0;
int col=0;

byte Square[8] = {    //block pixels where 1 refers to dark

0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111  
};

void setup() {
  
 Serial.begin(9600);
 bluetooth.begin(9600);
 
lcd.init();
lcd.backlight(); 
 
lcd.createChar(1,Square);   //create customization
lcd.home();                 //row , col 0
lcd.print("Loading");

for (int i=0; i<16 ;i++){   //for dashes
lcd.setCursor(col,1);       //at row 1,col 0
lcd.print("-");             //printing a dash 
col++;                      //all dashes in a line, instantly since no delay
}

col=0;  //block counts from start 

for (int i=0; i<16 ;i++){   //loading block style
 lcd.setCursor(col,1);      //at row 1 ,first dash
 lcd.write((byte)1);        //printing a block
 delay(100);                //wait a bit so one block at a time
 col++;                     //print till all blocks in a line
 }
delay(200);                 // wait a bit

lcd.clear();                //clear the screen 
lcd.print("Read here");     //displaying intro

lcd.cursor();               //cursor on for always
  
delay(2000);
lcd.clear();                //clear the screen again
lcd.noBacklight();            //light off
delay(500);

row=0;                      //reset the rows and columns
col=0; 
lcd.backlight();            //light on
}

void loop() {

if (bluetooth.available()){
  
char atPh=bluetooth.read();      //read bluetooth data and store in char "ph"
Serial.print(atPh);              //display those in serial monitor
if (row==0){                   //when the first word is at upper left corner
  
  lcd.setCursor(col,row);
  lcd.write(atPh);               //display those in LCD
  col++;                       //column increases as each word  //this is for a set of words


if (col>15){                   //when the maximum columns is reached
  row++;                       //increase the row and set the column to the beginning
  col=0;
}}

if (row==1){                   //in an increased row

  lcd.setCursor(col,row);
  lcd.write(atPh);             //display in LCD as above
  col++;

if (row==1 && col>15){         //when the screen is full
  delay(2000);                 //wait a moment so you can finish reading all the words
  
  lcd.clear();                 //clear the screen //light off //then light on  //reset the rows
  lcd.noDisplay();
  delay(500);
  lcd.display();
  row=0;
  col=0; 
}}

}


if (Serial.available()){
  char atCom=Serial.read();  
  bluetooth.write(atCom);    //display in ph's app
  Serial.print(atCom);       //also in serial monitor to check what you've sent  //optional
}
}
