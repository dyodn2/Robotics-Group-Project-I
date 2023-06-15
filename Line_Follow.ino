#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);
//##############################

int enablePin1 = 9;
int enablePin2 = 10;
int in1Pin = 2;
int in2Pin = 3;
int in3Pin = 4;
int in4Pin = 5;
boolean reverseL = 0;
boolean reverseR = 0;
const int maxSpeed = 138; // the range for speed 1s (0, 255)
/* variables to keep track of current speed of motors */
int leftServoSpeed = 0;
int rightServoSpeed = 0;
/* Define the pins for tfa iR sensors */
const int irPins[3] = {A3, A4, A5};
/* Define values for the IR sensor readings I */
int irSensorDigital[3] = {0, 0, 0};
int threshold = 500; // IR sensor threshold value For line detection
// binary representation of the sensor reading
// 1 when the sensor detects the line, 0 otherwise
int irSensors = B000;
// A score to determine deviation from the 1ine [-180 : +180].
// Negative means the robot is left of the line.
int error = 0;
int N=8;
int errorLast=0;
int count=0;

int del=0;

int z=30; //阻尼

// store the last value of error 

void setup ()
{
  pinMode (in1Pin, OUTPUT);
  pinMode (in2Pin, OUTPUT);
  pinMode (in3Pin, OUTPUT); 
  pinMode (in4Pin, OUTPUT);
  pinMode (enablePin1, OUTPUT); 
  pinMode (enablePin2, OUTPUT);
  //#########################
  Wire.begin();
  Serial.begin(9600);
  if(!adc.init()){
  Serial.println("ADS1115 not connected!");
  }
  //#########################
}

//#########################
float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}
//#########################


void loop ()
{
  del=0;
  Scan();
  UpdateDirection();
  Drive(leftServoSpeed, rightServoSpeed, del);
}

void Scan() {
  // Initialize the sensors
  irSensors = B000;
  int sensorValue=0;

  sensorValue = 1000*readChannel(ADS1115_COMP_0_GND);
  if (sensorValue >= threshold) irSensorDigital[0] = 1;
  else irSensorDigital[0] = 0;
  int b = 2;
  irSensors = irSensors + (irSensorDigital[0]<<b);
  
  sensorValue = 1000*readChannel(ADS1115_COMP_1_GND);
  if (sensorValue >= threshold) irSensorDigital[1] = 1;
  else irSensorDigital[1] = 0;
  b = 1;
  irSensors = irSensors + (irSensorDigital[1]<<b);

  sensorValue = 1000*readChannel(ADS1115_COMP_2_GND);
  if (sensorValue >= threshold) irSensorDigital[2] = 1;
  else irSensorDigital[2] = 0;
  b = 0;
  irSensors = irSensors + (irSensorDigital[2]<<b);
}

int over=0;
int flag=0;
void UpdateDirection() {

  flag=0;

  switch (irSensors) {

  case B000: // no sensor detects the lino
    if(errorLast > 0){error = 100; over=1;}
    else{error = -100; over=-1;}
    flag=1;
    break;
    

  case B100: // loft sensor on the lino
    if(over==-1){
      error=-z;
      over=0;
      flag=3;
    }else{
      error = -88;
    }
    break;

  case B110:
    if(over==-1){
      error=-z;
      over=0;
      flag=3;
    }else{
      error = -35;
    }
    break;

  case B010:
    if(over==-1){
      error=-z;
      over=0;
      flag=3;
    }
    else if(over==1){
      error=z;
      over=0;
      flag=3;
    }
    else{
      error = 1;
    }
    break;

  case B011:
    if(over==1){
      error=z;
      over=0;
      flag=3;
    }
    else{
      error = 35;
    }
    break;

  case B001: // righe sonzor on tho line
    if(over==1){
      error=z;
      over=0;
      flag=3;
    }else{
      error = 88;
    }
    break;

  case B111:
    if(over==-1){
      error=-z;
      over=0;
      flag=3;
    }
    else if(over==1){
      error=z;
      over=0;
      flag=3;
    }
    else {error=errorLast;}
    break;

  default:
    error = errorLast;
  }
  
  del=0;
  if (error > 0) {
    if(flag==1){
      leftServoSpeed = maxSpeed-35; 
      rightServoSpeed = 45-error;
    }
    else if(flag==3){
      leftServoSpeed = maxSpeed-error-100;
      rightServoSpeed = maxSpeed+90;
      del=1;
    }
    else{
      leftServoSpeed = maxSpeed; 
      rightServoSpeed = maxSpeed - error;
    }
  }

  else {
    if(flag==1){
      leftServoSpeed = 45+error;
      rightServoSpeed = maxSpeed-35;
    }
    else if(flag==3){
      leftServoSpeed = maxSpeed+90;
      rightServoSpeed = maxSpeed-100+error;
      del=1;
    }
    else{
      leftServoSpeed = maxSpeed + error;
      rightServoSpeed = maxSpeed;
    }
  }
  errorLast = error;
}

void Drive(int leftSpeed, int rightSpeed, int d) {
  
  int left = leftSpeed;
  int right = rightSpeed-3;

  reverseL=0;
  reverseR=0;
  // ensure input is in the correct range for motor control
  if(left <0) {
    left = 0-left;
    reverseL=1;
  }
  else if(left > maxSpeed) {left = maxSpeed;}

  if (right < 0) {
    right = 0-right;
    reverseR=1;
  }
  else if(right > maxSpeed) {right = maxSpeed;}

  if(d==1){
    setMotor(left, right, reverseL, reverseR);
    delay(80);
  }else{
    setMotor(left, right, reverseL, reverseR);
  } 
}


void setMotor(int leftServoSpeed, int rightServoSpeed, boolean reverseL, boolean reverseR)
{
  analogWrite(enablePin1, rightServoSpeed); //pwm the enable pin with the speed value for the right motor
  digitalWrite(in1Pin, ! reverseR);
  digitalWrite(in2Pin, reverseR);
  analogWrite(enablePin2, leftServoSpeed); //pwm the enable pin with the speed value for the left motor
  digitalWrite(in3Pin, ! reverseL);
  digitalWrite(in4Pin, reverseL);
}