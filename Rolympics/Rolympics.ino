//Title - A bluetooth car with two servos connected


#include <SoftwareSerial.h>   //including the libraries to use its function
#include <Servo.h>

//define the pins of motor

#define enA 5  //enable pins must be PWM digitalpins to be more efficient     
#define in1 3
#define in2 4
#define in3 7
#define in4 8
#define enB 6

char command;             //receive bluetooth command in character data type
String state="";
int Apos = 0;             //set the servo origin
int Bpos =180;

SoftwareSerial bluetooth(12,13);  //change arduino default RX,TX pins from 0 & 1 to any digitalpin  //(RX,TX) 
Servo servoA;                    //name the servo "servo"
Servo servoB; 

void setup() 
  {
    Serial.begin(9600);         //initiate serial communication
    bluetooth.begin(9600);      //initiate bluetooth communication
    servoA.attach(10);          //define servo pins //**PWM** digitalpins must be used
    servoB.attach(11);
    pinMode(enA,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(enB,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    servoA.write(Apos);
    servoB.write(Bpos);
  }

  

void loop() 
  {
    if (bluetooth.available())
    { 
        command= bluetooth.read();
        Serial.println(command);

          switch(command){
           case 'F' : forward(200,500);     //(speed,MovingTime)
                      break;
                      
           case 'B' : backward(180,500);
                      break;
                      
           case 'L' : left_forward(80,180); //Speed B should > Speed A  // A represents left side of the car and B for right side
                      break;
                      
           case 'R' : right_forward(180,80); // A>B
                      break;
                      
           case 'X' : right_backward(80,180);
                      break;
                      
           case 'S' : left_backward(180,80);
                      break;
                      
           case 'O' : ServoModeA(10); break;
                      
           case 'T' : ServoModeB(10); break;
           
           default  : Stop(); }   
        
    }
  }
    

/*******************************************************/


void forward(int Speed,int MOVINGTIME)
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,1);
    digitalWrite(in4,0);    
    analogWrite(enA,Speed);   //Although analogWrite function is used, PWM digitalpins should be connected
    analogWrite(enB,Speed);
    delay(MOVINGTIME);
    digitalWrite(in1,0);      //stop the car
    digitalWrite(in3,0);
  }

//////////////////////////////

 void backward(int Speed,int MOVINGTIME)
  {
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,0);
    digitalWrite(in4,1);    
    analogWrite(enA,Speed);
    analogWrite(enB,Speed);
    delay(MOVINGTIME);
    digitalWrite(in2,0);      //stop the car
    digitalWrite(in4,0);
  }

/////////////////////////////


 void right_forward(int SpeedA, int SpeedB)
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,1);    
    analogWrite(enA,SpeedA);
    analogWrite(enB,SpeedB);
  }

////////////////////////////

 void left_forward(int SpeedA, int SpeedB)
  {
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,1);
    digitalWrite(in4,0);    
    analogWrite(enA,SpeedA);
    analogWrite(enB,SpeedB);
  }

///////////////////////////

 void left_backward(int SpeedA, int SpeedB)   //same with right_forward //to fully left_backward, speed can be altered
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,1);    
    analogWrite(enA,SpeedA);
    analogWrite(enB,SpeedB);
  }

///////////////////////////

void right_backward(int SpeedA, int SpeedB)  //same with left_forward //to fully right_backward, speed can be altered
  {
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,1);
    digitalWrite(in4,0);    
    analogWrite(enA,SpeedA);
    analogWrite(enB,SpeedB);
  }

///////////////////////////

void Stop ()
  {
    digitalWrite(in1,0);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,0);
  }

//////////////////////////

void ServoModeA(int degree)
  {

    if (Apos>=180) {Apos=180;} 
    else {servoA.write(Apos += degree);} 
    if (Bpos<=0)   {Bpos=0;}   
    else {servoB.write(Bpos -= degree);} 
    
  }

/////////////////////////

  void ServoModeB(int degree)
  {

    if (Apos<=0)   {Apos=0;}   
    else {servoA.write(Apos -= degree);}  
    if (Bpos>=180) {Bpos=180;} 
    else {servoB.write(Bpos += degree);} 
    
  }

/////////////////////////

/* Notes :
 * Here, the left or right turning code, forward or backward whatever is basically the idea of rotating the car.
 * The car will move only "MOVINGTIME" milliseconds and stop for a sent character.(in forward and backward).
 * A switch should be soldered with battery wire to prevent unwanted dangers such as battery explosion.
 * A total of 4 PWM digitalpins are used with this code. 2 for enable pins, 2 for servos.
 * Neither of wheels is in motion if other commands are used through bluetooth.(like String or float) To change this, go to switch statement.
 * For all lines, A represents left side of the car and B for right side.
 * Use 1 servo if 2 servos is unstable.
 * In switch cases, T represents triangle, O for circle, X for cross and S for square, which are the button symbols of app.
 * At case O and case T, each turns the servos for each direction.
 * Each press of T or O will change the servos by 10 degree. It is changable.
 */
