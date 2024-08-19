joint seg1;
joint seg2;
joint seg3;

void setup(){
size (600,400);
seg1= new joint(150,200,0,300); //fixed 
seg2= new joint(seg1,330,100);
seg3= new joint(seg2,270,70);
}

void draw(){
background(204,153,255);  //red,green,blue

seg3.follow(mouseX,mouseY);
seg3.update();

seg2.connect(seg3.a.x,seg3.a.y);
seg2.update();

seg1.update();

seg1.show();
seg2.show();
seg3.show();

seg1.fixedJoint(seg2.a.x,seg2.a.y);

}
