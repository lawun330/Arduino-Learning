

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

int a=28;//rupper sit position 29
int b=36;//rlower leg sit position 38
int c=148;//upper sit left 146
int d=44;//lower sit left 48
int e=52;//rrupper sit 55
int f=36;//rrlower sit 24
int g=125;//lrupper sit 125
int h=42;//lrlower sit 47

int j=57;//rupper end for stand
int k=150;//timer increment




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
 

 upper.write(c);
 lower.write(d);
 rotate.write(80);
 rupper.write(a);
 rlower.write(b);
 rrotate.write(86);//80

 lrupper.write(g);
 lrmid.write(80);
 lrlower.write(h);

 rrupper.write(e);
 rrmid.write(89);//83
 rrlower.write(f);
 
 
 delay(10000);
 //delay(500000);
 
 
 
 
 

}

void loop() {
while (e<82) {//a<j
  a=(a+1);
  b= (b+2);
  c=(c-1);
  d=(d+2);
  e=(e+1);
  f=(f+2);
  g=(g-1);
  h=(h+2);

  upper.write(c);
 lower.write(d);
 rotate.write(80);
 rupper.write(a);
 rlower.write(b);
 rrotate.write(80);

 lrupper.write(g);
 lrmid.write(74);//80
 lrlower.write(h);

 rrupper.write(e);
 rrmid.write(86);//83
 rrlower.write(f);

 delay(k);
}

delay(500000);
delay(500000);
  
}
  


