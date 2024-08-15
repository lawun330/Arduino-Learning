/* This script demonstrates the use of millis() function. We can do something every 'interval' seconds. */


int previousTime = 0;
int interval = 5;  // 5 seconds


void setup() {
  Serial.begin(9600);
}


void loop() {
  unsigned long currentMillis = millis();        // start the continuous timer
  int currentTime = currentMillis / 1000;        // convert the timer to seconds
  int elapsedTime = currentTime - previousTime;  // subtract the previous time from the timer to get how much time has passed

  if (elapsedTime == interval)  // if every five seconds
  {
    previousTime = currentTime;  // update previousTime to currentTime
    Serial.println("hi");
  }
}


/* Example Description:
    * 'currentTime' is the total time in seconds since the program started.
    * The millis() function cannot be reset.
    * 
    * Once the 'currentTime' begins, it will keep counting.
    * 'previousTime' is not a counter like the 'currentTime'. It's the fixed time. It is 0.
    * 'interval' is our desired time interval. It is 5s in this case.
    * Let's assume 'interval' reaches 5s and 'previousTime' changes to 'currentTime' value at some points.
    * >> The 'elapsedTime' is 'currentTime' at first 5s (elapsedTime = currentTime - 0 = currentTime).
    * Check if 'elapsedTime' is equal to 'interval' (5s).
    * Update 'previousTime' to 5.
    * ### An action is performed here ###
    * 
    * 'currentTime' keeps counting.
    * Since 'currentTime' = 6 with 'previousTime' = 5, 'elapsedTime' starts from 1 again until it reaches another 5s again. 
    * (6 - 5 = 1s), (7 - 5 = 2s),  (8 - 5 = 3s),  (9 - 5 = 4s),...
    * >> Note that 'elapsedTime' is not 'currentTime' as in the previous example. 
    * >> It's 'currentTime' minus the 'previousTime' ('currentTime' - 'previousTime').
    * If 'currentTime' is 10, 'elapsedTime' is 5s (10 - 5 = 5s).
    * Check if 'elapsedTime' is equal to 'interval' (5s).
    * Update 'previousTime' to 10.
    * ### An action is performed here ###
    * 'currentTime' keeps counting.
    * 'currentTime' = 11 and 'previousTime' = 10 and we get 1 for 'elapsedTime'. 
    * (11 - 10 = 1s), (12 - 10 = 2s), (13 - 10 = 3s), (14 - 10 = 4s),...
    * When 'currentTime' is 15, 'elapsedTime' is 5s (15 - 10 = 5s).
    * Check if 'elapsedTime' is equal to 'interval' (5s).
    * Update 'previousTime' to 15.
    * ### An action is performed here ###
    * 
    * This process repeats, with 'elapsedTime' counting up from 0 to 'interval' each cycle.
    * 
    * Note: The actual time passed is always 1 second more than the interval because counting starts from 0.
 */