
#include "CytronMotorDriver.h"
#include "DueTimer.h"

//Define statements for the motor driver
//Todo: Change the pin numbers 
#define LeftLineFollower 32 
#define MiddleLineFollower 33
#define RightLineFollower 34 

//Define statements for the ultrasonic sensor
#define trigPinRight 10
#define echoPinRight 13

#define trigPinLeft 11
#define echoPinLeft 12

//Define statements for the motor driver
CytronMD motor(PWM_DIR, 2, 9);  
CytronMD motor3(PWM_DIR, 5, 6); 

CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);

//Define statements for the line follower
const int whitelvl = 0;
const int blacklvl = 1;

long duration;
int distance;

//Func for the movement forward 
void run_fwd()
{
  motor.setSpeed(255);  
  motor2.setSpeed(255);  
  motor3.setSpeed(255);  
  motor4.setSpeed(255);  
  Serial.println("Forward");
}

//Func for the movement backward
void run_bwd(){
  motor.setSpeed(-255);  
  motor2.setSpeed(-255);  
  motor3.setSpeed(-255);  
  motor4.setSpeed(-255);
  Serial.println("Backward");
}

//Func for the movement left
void run_lft()
{
  motor.setSpeed(-255);  
  motor2.setSpeed(-255);  
  motor3.setSpeed(255);  
  motor4.setSpeed(255);
  Serial.println("Left");
}

//Func for the movement right
void run_rgt()
{
  motor.setSpeed(255);  
  motor2.setSpeed(255);  
  motor3.setSpeed(-255);  
  motor4.setSpeed(-255);
  Serial.println("Right");
}

void run_stop()
{
  motor.setSpeed(0);  
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
}

void linesensorPoll() 
{
    int left = digitalRead(LeftLineFollower);
    int middle = digitalRead(MiddleLineFollower);
    int right = digitalRead(RightLineFollower);

    //Todo: Change the if statements to fit the line follower better
    if ((left == whitelvl) && (middle < whitelvl) && (right > blacklvl)) 
    {
        run_lft();
    }
    else if ((left > blacklvl) && (middle < whitelvl) && (right > blacklvl)) 
    {
        run_rgt();
    }
    else if ((left > blacklvl) && (middle > blacklvl) && (right > blacklvl)) 
    {
        run_bwd();
    }
    else 
    {
        run_fwd();
    }
}

void ultrasonicSensorPoll(int trigPin, int echoPin, bool turnLeft) 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance < 30)
  { 
    if (turnLeft) 
    {
      run_lft(); 
    } 
    else 
    {
      run_rgt(); 
    }
  } 
  else 
  {
    run_fwd(); 
  }
}

void setup() 
{
  Serial.begin(9600);
  Timer.attachInterrupt(linesensorPoll).setFrequency(20).start();
  Timer1.attachInterrupt([] { ultrasonicSensorPoll(trigPinLeft, echoPinLeft, false); }).setFrequency(10).start(); 
  Timer2.attachInterrupt([] { ultrasonicSensorPoll(trigPinRight, echoPinRight, true); }).setFrequency(10).start(); 
}

void loop() {
  
}
