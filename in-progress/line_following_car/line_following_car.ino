/* This script uses IR sensors and motors to create a car that follows a black-painted path. 
A PID controller is implemented to smooth out that process.
Turning of coefficients is done by changing the Kp, Ki, and Kd values.
This kind of car is commonly known as "Line Follower". */


// IR sensors
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3

// motors
#define IN1 7
#define IN2 6
#define ENA A4
#define IN3 5
#define IN4 4
#define ENB A5

// mathematical constants
#define targetVal 0  // Target value
#define Kp 0.05      // Proportional gain
#define Kd 0.05      // Derivative gain
#define Ki 0.01      // Integral gain
#define lb 0         // lower bound PWM output // equivalent to car speed
#define ub 255       // upper bound PWM output // equivalent to car speed

// variables
double current_time;
double last_time = 0.0;
double current_error;
double last_error = 0.0;
double proportional = 0.0;
double derivative = 0.0;
double integral = 0.0;


void setup() {
  Serial.begin(9600);
  Serial.println("Program starts!");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // initialize the motors to stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void loop() {
  double currentVal = getIRFeedback();
  double output = getPIDControllerOutput(targetVal, currentVal);
  // Serial.print("\t");
  // Serial.println(output);
  driveCar(output);
}

/**********************************************************/

// function to get the IR sensors' reading
float getIRFeedback() {
  double current_sensors_readings = (analogRead(IR1) + analogRead(IR2)) - (analogRead(IR3) + analogRead(IR4));
  /*Serial.print(analogRead(A0));
  Serial.print("\t");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.print("\t");
  Serial.print(analogRead(A3));
  Serial.print("\t");*/
  return current_sensors_readings;
}


// function that uses Proportional-Integral-Derivative (PID) controller to get the control output
float getPIDControllerOutput(float targetVal, float currentVal) {
  current_time = millis();                          // get the current time in milliseconds
  double value;                                     // declare a variable to store the control output
  double dt = (current_time - last_time) / 1000.0;  // calculate the time difference (delta time) in seconds

  if (dt == 0) {  // avoid division by zero
    dt = 1;       // set dt to 1 second if it is zero
  }

  current_error = targetVal - currentVal;                             // calculate the error as the difference between the target and the current sensor reading
  proportional = current_error;                                       // the proportional term is directly the error
  integral += current_error * dt;                                     // calculate the integral term as the sum of the error over time
  derivative = (current_error - last_error) / dt;                     // calculate the derivative term as the rate of change of the error
  value = (Kp * proportional) + (Ki * integral) + (Kd * derivative);  // calculate the control output using the PID formula

  last_time = current_time;    // update the last time to the current time
  last_error = current_error;  // update the last error to the current error
  return value;                // return the control output
}


// function to drive the car to follow the line
void driveCar(float val) {
  // calculate speed
  int a = 140 - val;
  int b = 140 + val;

  // ensure the speed is within the bounds
  constrain(a, lb, ub);
  constrain(b, lb, ub);

  // drive car forward with varying speeds for two wheels
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, a);
  analogWrite(ENB, b);

  Serial.println("val: " + String(val) + "\t" + "a: " + String(a) + "\t" + "b: " + String(b));  // debugging print
}
/**********************************************************/
