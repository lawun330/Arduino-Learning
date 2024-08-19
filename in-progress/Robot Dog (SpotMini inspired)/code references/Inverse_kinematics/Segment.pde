class joint
{
  PVector a;
  float angle;
  float Length;
  PVector b=new PVector(); //set the vector once 
  joint parent =null ;  //the first time is null valued
  int sw;
  
  //A(x,y) point and initial angle with length of a fixed joint
  joint(float x,float y,float angle_ , float Length_){
    a=new PVector (x,y);  //create a point A
    sw=7;
    angle=angle_;
    Length=Length_;
    calculateB();
  }
  
 //joint connected to fixed joint 
  joint(joint parent_,float angle_, float Length_){
    parent= parent_;
    a=parent.b.copy(); //its A(x,y) is B (x,y) of fixed joint
    sw=6;
    Length=Length_;
    angle=angle_;
    calculateB();
  }

//fixed joint
void fixedJoint(float tx,float ty){
  PVector target = new PVector (tx,ty);
  PVector dir = PVector.sub(target,a);  //new vector=(target X- aX),(targetY - aY)
  
  
}  

void connect(float tx,float ty){
  PVector target = new PVector (tx,ty);
  PVector dir = PVector.sub(target,a);  
  angle = dir.heading(); 
 //dir.setMag(Length);
 //dir.mult(-1);
 //a=PVector.add(target,dir);
}

//following the mouse
void follow(float tx,float ty){
  PVector target = new PVector (tx,ty);
  PVector dir = PVector.sub(target,a);  //new vector=(target X- aX),(targetY - aY)
  angle = dir.heading(); //the heading of that vector  //A----->B  Tpoint
    
  //the same length with opposite direction B<-----ATpoint
  //dir.setMag(Length);
  dir.mult(-1);
  
  //the reversed direction point is now A(x,y)
  a=PVector.add(target,dir);
}

//setting the point B
void calculateB(){
  float dx= Length * cos(angle);
  float dy= Length * sin(angle);
  //setting is replacing, not creating a new PVector
  b.set(a.x+dx,a.y+dy);//a(x,y) with value dx and dy
}

void update(){
  calculateB();
}

//making the line AB
void show(){
  stroke(0); //stroke(colour intensity of a line)
  strokeWeight(sw); //thickness of a line
  line(a.x,a.y,b.x,b.y); //first x-coordinate, first y-coordinate, sec x-coordinate, sec y-coordinate
}
}
