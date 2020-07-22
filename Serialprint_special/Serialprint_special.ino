// smart serial printing in array with comma and ending 

int no=10;
int i;
bool Stop=false;
void setup() {
Serial.begin(9600);
Serial.print("Numbers are {");
}

void loop() {
 for (i=1; i<(no-1) ; i++){
  Serial.print(i);
  Serial.print(", ");
 }
 if (i=no){
  Serial.print(i);
  Serial.print("}");
  Stop=true;
  }
  while (Stop){}
}
