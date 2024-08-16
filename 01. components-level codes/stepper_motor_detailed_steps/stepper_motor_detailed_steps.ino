/* This script illustrates the use of the stepper motor.
There are 2040 steps for a full cycle.
NOTE: The stepper motor does not rotate like DC motors.
Example - To perform a full cycle rotation, the step() function with the argument 2040 --> step(2040) can be used.
        - Ideally, you can set the 'steps_per_time' to 2040, to rotate the stepper motor a full cycle without any delay.
        - Practically, in that case, the stepper motor becomes hot and does not rotate. 
Recommendation: Rotate 'x' steps at a time with the speed 'y' RPM to reach a total of 'z' steps. 
                The speed 14 RPM is preferable. */


#include <Stepper.h>

int steps_per_time = -500;  // 'steps_per_time' (500 steps) represents how many steps it should rotate at a time
int rpm_speed = 20;         // rotate with the speed of 'rpm_speed' RPM (20 RPM)
int total_steps = 2000;     // the stepper motor continues to rotate until 'total_steps' (2000 steps) is reached

Stepper my_motor(steps_per_time, 8, 9, 10, 11);


void setup() {
  Serial.begin(9600);
  my_motor.setSpeed(rpm_speed);  // set the rotation speed
  my_motor.step(total_steps);    // rotate until the specific steps is reached
}


void loop() {}
