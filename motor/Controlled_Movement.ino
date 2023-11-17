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
#include "Timer1One.h"
#define WDT_KEY (0xA5)

void watchdogSetup(void) {
  /*** watchdogDisable (); ***/
}

void setup()
{
  // Enable watchdog.
  WDT->WDT_MR = WDT_MR_WDD(0xFFF)
                | WDT_MR_WDRPROC
                | WDT_MR_WDRSTEN
                | WDT_MR_WDV(256 * 2);

  Serial.begin(250000);
  uint32_t status = (RSTC->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> 8;
  Serial.print("RSTTYP = 0b"); Serial.println(status, BIN); 
}

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

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(50000);
  Time.attachInterrupt(sensorPoll);
}

void sensorPoll() 
{
  int left = digitalRead(LeftLineFollower);
  int middle = digitalRead(MiddleLineFollower);
  int right = digitalRead(RightLineFollower);

  //Todo: Change the if statements to fit the line follower better
  if ((left < whitelevl) && (middle < whitelvl) && (right > blacklvl)) 
  {
    run_lft();
  }
  else if ((left > blacklvl) && (middle < whitelvl) && (right > blacklvl)) {
    run_rgt();
  }
  else if ((left > blacklvl) && (middle > blacklvl) && (right > blacklvl)) {
    run_bwd();
  }
  else {
    run_fwd();
  }
}

void loop() {
  
  
}
void loop()
{
  WDT->WDT_CR = WDT_CR_KEY(WDT_KEY)  // Restart timer
                | = WDT_CR_WDRSTT;

  Serial.println("Restart watchdog");
  delay(500);

  while (true)
  {
    Serial.println("Deadlock!");
    delay(500);
  }

  // int left = digitalRead(LeftLineFollower);
  // int middle = digitalRead(MiddleLineFollower);
  // int right = digitalRead(RightLineFollower);

  //WASD control
  // if (Serial.available() > 0) {
  //   char data = Serial.read();
  //   if (data == 'w') {
  //     run_fwd();
  //   }
  //   else if (data == 's') {
  //     run_bwd();
  //   }
  //   else if (data == 'a') {
  //     run_lft();
  //   }
  //   else if (data == 'd') {
  //     run_rgt();
  //   }
  //   else if (data == 'x') {
  //     run_stop();
  //   }
  // }
}
