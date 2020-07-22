//a simple math game through serial monitor

int fixedtime=0;
int score=0;
int requiredtime=10;
int x=1;

void setup() 
  {
    Serial.begin(9600);
    Serial.println("Welcome to math game!!");
  }

void loop() 
  { 
    Serial.println("Press 'S' to start");
    Serial.println();

    if (Serial.available())
      {
        start : char ch=Serial.read();
        while (ch=='S')
          {
//timer starts  
  
           int Time=millis()/1000;
           int count= Time-fixedtime;
    
           if (Time>fixedtime+requiredtime-1)     //This helps to do something whenever 'requiredtime' seconds using millis() function
             { 
              fixedtime=millis()/1000;
             }

//every 10s passes, show the score

           if (count==requiredtime)
              { 
                Serial.println();
                Serial.print("YOUR SCORE IS ");
                Serial.println(score);
                Serial.println();
                break;
              }

           else { 

//ask the question with random number
    
    Serial.print("Find the square of ");  
    int randomVal=random(2-10);
    Serial.println(randomVal);            

//compute the correct answer    
  
    int answer=randomVal*randomVal;

//display what player types  
    
    wait : int typednumber=Serial.parseInt();
    int Time=millis()/1000;
    int count= Time-fixedtime;
    
        if (Time>fixedtime+requiredtime-1)         
          { 
            fixedtime=millis()/1000;
          }
  
//while waiting, if 10s passes, show the score
         if (count==requiredtime)
          { 
            Serial.println();
            Serial.print("YOUR SCORE IS ");
            Serial.println(score);
            Serial.println();
            Serial.println("Press 'S' to start");
            break;   
          }
    
//if nothing is typed, wait 
    if (typednumber==0)
      {
        goto wait;
      }

    else
      {
        Serial.print("You typed : ");
        Serial.println(typednumber);
        Serial.println();
      }
      
//check and add the score if he is right  
    if (typednumber==answer)
      {
        score++;
      } 
      }

      }
      }
      
    if (!Serial.available())
      {
        goto start;
      }
  }
  
