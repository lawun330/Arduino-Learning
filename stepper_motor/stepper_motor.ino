#include <Stepper.h>

//the motor has 2040steps for full cycle //14rpm is most used

int x=-500; int z=20; int y=2000;
Stepper motor(x,8,9,10,11);
// x in here means how much steps it goes at a time

void setup() {
  Serial.begin(9600);
motor.setSpeed(z); 

motor.step(y);
  

//one use of step(y) function determines the motor to rotate until "y"total steps is achieved
//the moving speed is determined by setSpeed(z) function
}

void loop() {
}

// x=500 , the motor must rotate 500 steps at a time
//step(y=2000)  ,  it will continue to rotate until 2000 steps is achieved
//setSpeed(z=18) , it will rotate with the speed of 18RPMs for the following step() function

/*eg. You need only one line of step(y=2040) if you want to rotate only one revolution for final position, you may determine for 
the motor to move continuous 2040 steps(by setting x=2040)**HIGHLY UNRECOMMENDED because the motor becomes hot and doesn't rotate**
or steps by steps by defining x (ie. x steps at a time until y steps is achieved with the speed of z)*/
