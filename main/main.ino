#include "Simpletimer.h"
#include "CytronMotorDriver.h"
#include <cstdlib>
// Define statements for the motor driver
// Todo: Change the pin numbers 
#define MiddleLineFollower A7
#define RightLineFollower A6
#define LeftLineFollower A5

#define trigPinRight 10
#define echoPinRight 13
#define trigPinLeft 12
#define echoPinLeft 11

const int blackLineThreshold = 1000;

CytronMD motor(PWM_DIR, 2, 9);
CytronMD motor3(PWM_DIR, 5, 6); 
CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);

Simpletimer lineTimer{};
Simpletimer rightUSTimer{};
Simpletimer leftUSTimer{};




void run_fwd()
{
  motor.setSpeed(200);  
  motor2.setSpeed(200);  
  motor3.setSpeed(200);  
  motor4.setSpeed(200);  
  //Serial.println("Forward");
}

void run_bwd(){
  motor.setSpeed(-200);  
  motor2.setSpeed(-200);  
  motor3.setSpeed(-200);  
  motor4.setSpeed(-200);
  Serial.println("Backward");
}

void run_stop()
{
  motor.setSpeed(0);  
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
}

void run_lft()
{
  motor.setSpeed(-200);  
  motor2.setSpeed(-200);  
  motor3.setSpeed(200);  
  motor4.setSpeed(200);
  Serial.println("Left\n");
}
void run_rgt()
{
  motor.setSpeed(200);  
  motor2.setSpeed(200);  
  motor3.setSpeed(-200);  
  motor4.setSpeed(-200);
  Serial.println("Right\n");
}

void checkBlackLine() {
    volatile int middleSensorValue = analogRead(MiddleLineFollower);
    volatile int rightSensorValue = analogRead(RightLineFollower);
    volatile int leftSensorValue = analogRead(LeftLineFollower);
    int counter = 0;

     // Print out the sensor values
    Serial.print("Middle sensor value: ");
    Serial.println(middleSensorValue);
    //delay(500);
    Serial.print("Right sensor value: ");
    Serial.println(rightSensorValue);
    //delay(500);
    Serial.print("Left sensor value: ");
    Serial.println(leftSensorValue);

     if (middleSensorValue > blackLineThreshold && leftSensorValue > blackLineThreshold || rightSensorValue > blackLineThreshold && middleSensorValue > blackLineThreshold) {
        run_stop();
        Serial.println("Black line detected");
        run_bwd();
        delay(400);
        run_lft();
        delay(700);

        middleSensorValue = 0;
        rightSensorValue = 0;
        leftSensorValue = 0;
        
    } else {
        run_fwd();
        Serial.println("No black line detected");
    }
    counter++;
}


// ULTASONIC
void checkObj(int trigPin, int echoPin, bool turnLeft)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  
  if (distance < 25)
  { 
    if (turnLeft) 
    {
      Serial.println("Distance:" + distance);
      Serial.println("Right Sensor: Object Detected");
      run_stop();
      run_lft();
      delay(1000);
      run_fwd();
    } 
    else 
    {
      Serial.println("Left Sensor: Object Detected");
      run_stop();
      run_rgt();
      delay(1000);
      run_fwd();
    }
  } 
  else
  {
    run_fwd();
  }
}

void setup() {

  pinMode(MiddleLineFollower, INPUT);
  pinMode(RightLineFollower, INPUT);
  pinMode(LeftLineFollower, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

  pinMode(13, OUTPUT);

  Serial.begin(9600);

  lineTimer.register_callback(checkBlackLine);
  rightUSTimer.register_callback([]() { checkObj(trigPinLeft, echoPinLeft, false); });
  leftUSTimer.register_callback([]() { checkObj(trigPinRight, echoPinRight, true); });
}

void loop() {
  // lineTimer.run(100);
  rightUSTimer.run(150);
  leftUSTimer.run(150);
}