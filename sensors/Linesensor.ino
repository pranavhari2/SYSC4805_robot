/**
 * This code is for the controlled movement of the robot.
 * We will be using this as the base as the movement for the robot
 * some of the line follower code is commented out as we are not using it right now
 * 
 * @file Controlled_Movement.ino
 * @brief Controlled movement of the robot
 * @author Pranav K Hari, 101144482
 * @author Christpher Semaan, 101140813
 * @author Sagar Syal, 101150341
 * @version 1.0
 * 
*/

#include "CytronMotorDriver.h"
#include "DueTimer.h"

//Define statements for the motor driver
//Todo: Change the pin numbers 
#define MiddleLineFollower A7
#define RightLineFollower A6
#define LeftLineFollower A5


 
//Define statements for the motor driver
CytronMD motor(PWM_DIR, 2, 9);  
CytronMD motor3(PWM_DIR, 5, 6); 

CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);

//Define statements for the line follower
//Todo: Change the white and black levels to fit better
const int whitelvl = 600;
const int blacklvl = 850;

//Func for the movement forward 
void run_fwd(){Serial.println("Forward");}

//Func for the movement backward
void run_bwd(){Serial.println("Backward");}

//Func for the movement left
void run_lft(){Serial.println("Left");}

//Func for the movement right
void run_rgt(){Serial.println("Right");}

void sensorPoll() 
{
    int left = analogRead(LeftLineFollower);
    int middle =analogRead(MiddleLineFollower);
    int right = analogRead(RightLineFollower);

    Serial.print("Left: ");
    Serial.print(left);
    Serial.print(" Middle: ");
    Serial.print(middle);
    Serial.print(" Right: ");
    Serial.println(right);


}
