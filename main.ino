
#include "Simpletimer.h"
#include "CytronMotorDriver.h"
// Define statements for the motor driver
// Todo: Change the pin numbers 
#define MiddleLineFollower A7
#define RightLineFollower A6
#define LeftLineFollower A5

//Define statements for the ultrasonic sensor
#define trigPinRight 10
#define echoPinRight 13

#define trigPinLeft 12
#define echoPinLeft 11

CytronMD motor(PWM_DIR, 2, 9);
CytronMD motor3(PWM_DIR, 5, 6); 
CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);

// Define a timer object 
Simpletimer timer{};

long duration;
int distance = 0;

//Func for the movement forward 
void run_fwd()
{
  motor.setSpeed(128);  
  motor2.setSpeed(128);  
  motor3.setSpeed(128);  
  motor4.setSpeed(128);  
  Serial.println("Forward");
}

//Func for the movement backward
void run_bwd(){
  motor.setSpeed(-128);  
  motor2.setSpeed(-128);  
  motor3.setSpeed(-128);  
  motor4.setSpeed(-128);
  Serial.println("Backward");
}

//Func for the movement left
void run_lft()
{
  motor.setSpeed(-128);  
  motor2.setSpeed(-128);  
  motor3.setSpeed(128);  
  motor4.setSpeed(128);
  Serial.println("Left\n");
}

//Func for the movement right
void run_rgt()
{
  motor.setSpeed(128);  
  motor2.setSpeed(128);  
  motor3.setSpeed(-128);  
  motor4.setSpeed(-128);
  Serial.println("Right\n");
}

void run_stop()
{
  motor.setSpeed(0);  
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
}


void mock_runbwd(){
  Serial.println("Backward");
}

void mock_runfwd(){
  Serial.println("Forward");
}

// void linesensorPoll() 
// {
//     int left = digitalRead(LeftLineFollower);
//     int middle = digitalRead(MiddleLineFollower);
//     int right = digitalRead(RightLineFollower);

//     if ((left == blacklvl) && (middle == blacklvl) || (right == blacklvl) && (middle == blacklvl))
//     {
//         Serial.println("Black line detected");
//         Serial.println("LEFT: " + left);
//         Serial.println("MIDDLE: " + middle);
//         Serial.println("RIGHT: " + right);
//         //run_bwd();
//     }
//     else 
//     {
//         Serial.println("No Black line detected");
//         Serial.println("LEFT: " + left);
//         Serial.println("MIDDLE: " + middle);
//         Serial.println("RIGHT: " + right);
//         //run_fwd();
//     }
// }

void ultrasonicSensorPoll(int trigPin, int echoPin, bool turnLeft) 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println("Distance:" + distance);

  if (distance < 20)
  { 
    if (turnLeft) 
    {
      run_lft(); 
      Serial.println("Turning left");
    } 
    else 
    {
      run_rgt();
      run_stop(); 
    }
  } 
  else 
  {
    //run_fwd(); 
    Serial.println("Moving Forward");
  }
}

void ultrasonicSensorPollLeft()
{
  ultrasonicSensorPoll(trigPinLeft, echoPinLeft, false);
}

void ultrasonicSensorPollRight()
{
  ultrasonicSensorPoll(trigPinRight, echoPinRight, true);
}

// 
void checkBlackLine() {
    int middleSensorValue = analogRead(MiddleLineFollower);
    int rightSensorValue = analogRead(RightLineFollower);
    int leftSensorValue = analogRead(LeftLineFollower);
    //blackLineDetected = (middleSensorValue > 1500); // adjust the threshold as needed

     // Print out the sensor values
    Serial.print("Middle sensor value: ");
    Serial.println(middleSensorValue);
    Serial.print("Right sensor value: ");
    Serial.println(rightSensorValue);
    Serial.print("Left sensor value: ");
    Serial.println(leftSensorValue);

    if (middleSensorValue > 890 || leftSensorValue > 890 || rightSensorValue > 890) {
        Serial.println("BLACK LINE=========================================================");
        run_bwd();
        delay(1000);
        run_lft();
        delay(1000);
        run_stop();
        Serial.println("Black line detected");
    } else {
        run_fwd();
        Serial.println("No black line detected");
    }
}


void setup() {

    pinMode(MiddleLineFollower, INPUT);
    pinMode(RightLineFollower, INPUT);
    pinMode(LeftLineFollower, INPUT);
    Serial.begin(9600);
    timer.register_callback(checkBlackLine);

    pinMode(trigPinLeft, OUTPUT);
    pinMode(echoPinLeft, INPUT);
    pinMode(trigPinRight, OUTPUT);
    pinMode(echoPinRight, INPUT);
}


void loop() {
    timer.run(250);
}
