

#include <Servo.h>

Servo upper;
Servo lower;
Servo rotate;

Servo rupper;//right upper servo
Servo rlower;//right lower servo
Servo rrotate;//right sideways servo

Servo lrupper;
Servo lrmid;
Servo lrlower;

Servo rrupper;
Servo rrmid;
Servo rrlower;

int x=180;//upper sit position
int y=37;//lower leg sit position
int z=30;//time between leg movements

int q=170;//upper lr
int r=37;//lower lr

int a=10;//upper right sit position
int b=28;//lower right sit position

int c=10;//upper rr sit position
int d=28;


int ud=0;//0 for sit and 1 for stand
int countup=0;//counter to delay right front a bit

void setup() {
 upper.attach(1);
 lower.attach(3);
 rotate.attach(2);
 rupper.attach(4);
 rlower.attach(6);
 rrotate.attach(5);

 lrupper.attach(10);
 lrmid.attach(11);
 lrlower.attach(12);

 rrupper.attach(7);
 rrmid.attach(8);
 rrlower.attach(9);
 

 upper.write(150);
 lower.write(37);
 rotate.write(80);
 rupper.write(2);
 rlower.write(20);
 rrotate.write(80);

 lrupper.write(170);
 lrmid.write(80);
 lrlower.write(37);

 rrupper.write(10);
 rrmid.write(83);
 rrlower.write(14);
 
 
 delay(3000);
 
 
 

}

void loop() {

  upper.write(150);//sit
 lower.write(37);
 rotate.write(80);
 rupper.write(2);
 rlower.write(20);
 rrotate.write(83);

 lrupper.write(170);
 lrmid.write(80);
 lrlower.write(37);

 rrupper.write(10);
 rrmid.write(83);
 rrlower.write(14);

delay(10000);

 upper.write(105);//stand
 lower.write(85);
 rotate.write(80);
 rupper.write(40);
 rlower.write(80);
 rrotate.write(83);

 lrupper.write(130);
 lrmid.write(80);
 lrlower.write(78);

 rrupper.write(40);
 rrmid.write(83);
 rrlower.write(60);

 delay(15000);

}
