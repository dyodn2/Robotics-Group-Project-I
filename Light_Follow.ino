int enablePin1 = 9;
int enablePin2 = 10;
int in1Pin = 2;
int in2Pin = 3;
int in3Pin = 4;
int in4Pin = 5;

int sensDiffThresh = 60;
int mid = 90;
int qick = 160;

int SensorLeft = 0;
int SensorRight = 0;
/* Define the pins for the light sensors */
int LeftSensor = A2; // This stores the value of the Left Sensor pin to use later on in the sketch
int RightSensor = A1; // This stores the value of the Right Sensor pin to use later on in the sketch
const int baseSpeed = 160;
const int foreSpeed = 240;
double c=1.33;
double bias=0.55;
double slow=0.4;

/* Define variables for the LDR Sensor readings and the difference between the two */
int SensorDifference = 0; // This value is used to determine the difference between the Left and Right
int error = 3;// difference between motors for turning

int leftServoSpeed = 0;
int rightServoSpeed = 0;

void setup ()
{
  pinMode (in1Pin, OUTPUT); 
  pinMode (in2Pin, OUTPUT); 
  pinMode (in3Pin, OUTPUT); 
  pinMode (in4Pin, OUTPUT) ; 
  pinMode (enablePin1, OUTPUT) ; 
  pinMode (enablePin2, OUTPUT) ;
}

void loop ()
{
  boolean reverse = 0; //digitalRead (switchPin);
  SensorLeft = 1023-analogRead (LeftSensor); // This reads the valse of the sensor, then saves it to the corresponding integer.
  delay (1); // delay to let ad settle
  SensorRight = 1023-analogRead (RightSensor); // This reads the value of the sensor, then saves it to the corresponding integer.
  // SensorLeft=1.08*SensorLeft;
  delay (1); // delay to let ad settle
  SensorDifference = abs(SensorLeft-SensorRight); // This calculates the difference between the two sensors and then saves it to an integer.

  if(SensorRight<180&&SensorLeft<180){
    leftServoSpeed = 0; 
    rightServoSpeed = 0; 
    setMotor (leftServoSpeed, rightServoSpeed, reverse);
  }

  else{
    if (SensorDifference < sensDiffThresh) 
    { // This is interpreted as if the difference between the two sensors is less than the threshold
      // (Experiment to suit our sensors), Do this:
      leftServoSpeed = foreSpeed+error; // This is used to go straight
      rightServoSpeed = foreSpeed; // both motors are enabled to go forward.
    }
    
    else if(SensorDifference < mid){
      if (SensorLeft > SensorRight) 
      { // This is interpreted as if the Left sensor reads more light than the Right Sensor, Do this:
        leftServoSpeed = foreSpeed-30; // This is used to turn left making the left servo much slower than the right servo
        rightServoSpeed = foreSpeed; // opposite motor runs to turn Left
      }

      if (SensorLeft < SensorRight) 
      { // This is interpreted as if the Left sensor reads less light than the Right Sensor, Do this:
        leftServoSpeed = foreSpeed; // This is used to go right
        rightServoSpeed = foreSpeed-30; // This is used to turn right making the left servo much slower than the left servo.
      }
    }

    else if(SensorDifference < qick){
      if (SensorLeft > SensorRight) 
      { // This is interpreted as if the Left sensor reads more light than the Right Sensor, Do this:
        leftServoSpeed = baseSpeed+25; // This is used to turn left making the left servo much slower than the right servo
        rightServoSpeed = baseSpeed+25+slow*(SensorDifference-30); // opposite motor runs to turn Left
      }

      if (SensorLeft < SensorRight) 
      { // This is interpreted as if the Left sensor reads less light than the Right Sensor, Do this:
        leftServoSpeed = baseSpeed+25+slow*(SensorDifference-30); // This is used to go right
        rightServoSpeed = baseSpeed+25; // This is used to turn right making the left servo much slower than the left servo.
      }
    }

    else{
      if (SensorLeft > SensorRight)
      { // This is interpreted as if the Left sensor reads more light than the Right Sensor, Do this:
        leftServoSpeed = baseSpeed-bias*(SensorDifference-90); // This is used to turn left making the left servo much slower than the right servo
        rightServoSpeed = baseSpeed+c*(SensorDifference-90); // opposite motor runs to turn Left
      }

      if (SensorLeft < SensorRight) 
      { // This is interpreted as if the Left sensor reads less light than the Right Sensor, Do this:
        leftServoSpeed = baseSpeed+c*(SensorDifference-90); // This is used to go right
        rightServoSpeed = baseSpeed-bias*(SensorDifference-90); // This is used to turn right making the left servo much slower than the left servo.
      }
    }

    if(leftServoSpeed>250) leftServoSpeed=250;
    if(leftServoSpeed<30) leftServoSpeed=30;
    if(rightServoSpeed>250) rightServoSpeed=250;
    if(rightServoSpeed<30) rightServoSpeed=30;
    setMotor (leftServoSpeed, rightServoSpeed, reverse);
  }
}

void setMotor (int leftservospeed, int rightservospeed, boolean reverse)
{
  analogWrite (enablePin2, rightServoSpeed); //pwm the enable pin with the speed value for the right motor 
  digitalWrite (in1Pin, ! reverse); 
  digitalWrite (in2Pin, reverse);
  analogWrite (enablePin1, leftServoSpeed); //pwm the enable pin with the speed value for the left motor 
  digitalWrite (in3Pin, ! reverse); 
  digitalWrite (in4Pin, reverse);
}


