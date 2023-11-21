
#include "CytronMotorDriver.h"
#include "DueTimer.h"

//Define statements for the motor driver
//Todo: Change the pin numbers 
#define MiddleLineFollower 30
#define RightLineFollower 32
#define LeftLineFollower 34

//Define statements for the ultrasonic sensor
#define trigPinRight 10
#define echoPinRight 13

#define trigPinLeft 12
#define echoPinLeft 11

//Define statements for the motor driver
CytronMD motor(PWM_DIR, 2, 9);  
CytronMD motor3(PWM_DIR, 5, 6); 

CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);


//Define statements for the line follower
const int whitelvl = 0;
const int blacklvl = 1;

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

void linesensorPoll() 
{
    int left = digitalRead(LeftLineFollower);
    int middle = digitalRead(MiddleLineFollower);
    int right = digitalRead(RightLineFollower);

    if ((left == blacklvl) && (middle == blacklvl) || (right == blacklvl) && (middle == blacklvl))
    {
        Serial.println("Black line detected");
        Serial.println("LEFT: " + left);
        Serial.println("MIDDLE: " + middle);
        Serial.println("RIGHT: " + right);
        //run_bwd();
    }
    else 
    {
        Serial.println("No Black line detected");
        Serial.println("LEFT: " + left);
        Serial.println("MIDDLE: " + middle);
        Serial.println("RIGHT: " + right);
        //run_fwd();
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

void setup() 
{

  pinMode(LeftLineFollower, INPUT);
  pinMode(MiddleLineFollower, INPUT);
  pinMode(RightLineFollower, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

  Serial.begin(38400);
  
  //Timer1.attachInterrupt(ultrasonicSensorPollLeft).start(); 
  //Timer2.attachInterrupt(ultrasonicSensorPollRight).start(); 
}         

void loop() {
    // delay(2000);
    // Timer.start();

    // delay(2000);
    // Timer.stop();

    Timer.attachInterrupt(linesensorPoll).setFrequency(50).start();
    delay(1000);
    Timer.stop();

    // delay(500);
    // Timer1.start();

    // delay(500);
    // Timer1.stop();

    // delay(500);
    // Timer2.start();

    // delay(500);
    // Timer2.stop();
}

// void firstHandler(){
//     Serial.println("[-  ] First Handler!");
// }

// void secondHandler(){
//     Serial.println("[ - ] Second Handler!");
// }

// void thirdHandler(){
//     Serial.println("[  -] Third Handler!");
// }

// void setup(){
//     Serial.begin(9600);

//     Timer3.attachInterrupt(firstHandler).start(500000); // Every 500ms
//     Timer4.attachInterrupt(secondHandler).setFrequency(1).start();
//     Timer5.attachInterrupt(thirdHandler).setFrequency(10);
// }

// void loop(){
//     delay(2000);
//     Timer5.start();

//     delay(2000);
//     Timer5.stop();
// }
