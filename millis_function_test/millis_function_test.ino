//do something every y seconds


int x=0;
int y=5;

void setup() {
Serial.begin(9600);
}

void loop() {
int a = millis()/1000;  //add the timer
int Count=a - x;        //timer-fixed timer

Serial.println(Count);
delay(1000);

if (a>x+y-1)            //if every five seconds
{
  x=millis()/1000;      //change the fixed timer value
  Serial.println("hi");
}
}

/* millis function cannot be reset. This means 'a' will be total time.
 * To explain the programme flow : fixed time 'x' is 0 at first.The time 'a' begins. 
 * Let's say 'y'=5 where y is the time interval we want and 'x' changes to 'a' value at some points.
 * The count function results in 'a' since a-0=a at first 5 seconds.
 * Check if 'a' is larger than 0+5-1=4.If 'a' is larger than 4s which means it has already reached 5s, 'x' changed to 5.
 * 'a' continues to count. a=6 then x=5 and count starts from 1 again. 
 * 6-5=1, 7-5=2,  8-5=3,  9-5=4 and notice that result value is not real time. It's total subtracts(-) fixed value.
 * If a=10 which means we have reached another 5s, then counter=10-5=5 displayed again but x+y-1=5+5-1= '9'. 
 * So a=10> 9, then 'x' changed to 10.
 * a=11 then x=10 and we get 1 back. 11-10=1, 12-10=2,  13-10=3,  14-10=4,  15-10=5.
 * When 'a' is 15. x+y-1= 10+5-1=14. a>14 and 'x' has changed to 15 so that time is reset and
 when 'a' continues to 16, 16-15=1 we get 1 again.
 * The important thing is although it shows till 5s each time, the actual passed time is 6s because the reset time 0s counts as 1s actually. 
 
 
 */
