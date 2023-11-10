#include "CytronMotorDriver.h"

//Define statements for the motor driver
//Todo: Change the pin numbers 
#define LeftLineFollower 32 
#define MiddleLineFollower 33
#define RightLineFollower 34 

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
void run_fwd()
{
  motor.setSpeed(255);  
  motor2.setSpeed(255);  
  motor3.setSpeed(255);  
  motor4.setSpeed(255);  
  Serial.println("Forward");
}

//Func for the movement backward
void run_bwd()
{
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

//Func for the movement stop
void run_stop()
{
  motor.setSpeed(0);  
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  int left = digitalRead(LeftLineFollower);
  int middle = digitalRead(MiddleLineFollower);
  int right = digitalRead(RightLineFollower);
 
  //Todo: Change the if statements to fit the line follower better
  // if (left < whitelevl && middle < whitelvl && right > blacklvl) 
  // {
  //   run_lft();
  // }
  // else if (left > blacklvl && middle < whitelvl && right > blacklvl) {
  //   run_rgt();
  // }
  // else if (left > blacklvl && middle > blacklvl && right > blacklvl) {
  //   run_bwd();
  // }
  // else {
  //   run_fwd();
  // }

  //WASD control
  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == 'w') {
      run_fwd();
    }
    else if (data == 's') {
      run_bwd();
    }
    else if (data == 'a') {
      run_lft();
    }
    else if (data == 'd') {
      run_rgt();
    }
    else if (data == 'x') {
      run_stop();
    }
  }
  
}
