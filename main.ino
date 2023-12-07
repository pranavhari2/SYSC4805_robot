/**
 * @file    RobotControl.cpp
 * @brief   Control script for a snow plow robot using line sensor, ultrasonic, and IR sensors.
 *          This script allows the robot to navigate by avoiding obstacles and lines.
 * @author  Pranav Koduvely Hari, 101144482
 * @author Christopher Semaan, 101140813
 * @author Sagar Syal, 101150341
 * @date    2023-12-05
 */

#include "Simpletimer.h"
#include "CytronMotorDriver.h"
#include <cstdlib>

// Pin definitions for line followers and ultrasonic sensors
#define MiddleLineFollower A7
#define RightLineFollower A6
#define LeftLineFollower A5

#define trigPinRight 10
#define echoPinRight 13
#define trigPinLeft 12
#define echoPinLeft 11

#define IRpin 40

// Threshold value to detect a black line
const int blackLineThreshold = 900;

// Motor driver initialization
CytronMD motor(PWM_DIR, 2, 9);  // motor 1
CytronMD motor3(PWM_DIR, 5, 6); // motor 3
CytronMD motor2(PWM_DIR, 4, 3); // motor 2
CytronMD motor4(PWM_DIR, 8, 7); // motor 4

// Timer objects for different sensors
Simpletimer lineTimer{};
Simpletimer rightUSTimer{};
Simpletimer leftUSTimer{};
Simpletimer IRtimer{};

// Variables to store sensor readings
volatile int middleSensorValue;
volatile int rightSensorValue;
volatile int leftSensorValue;

/**
 * @brief Runs motors forward at a set speed.
 */
void run_fwd()
{
  motor.setSpeed(200);  
  motor2.setSpeed(200);  
  motor3.setSpeed(200);  
  motor4.setSpeed(200);  
  //Serial.println("Forward");
}

/**
 * @brief Runs motors backward at a set speed.
 */
void run_bwd(){
  motor.setSpeed(-200);  
  motor2.setSpeed(-200);  
  motor3.setSpeed(-200);  
  motor4.setSpeed(-200);
  Serial.println("Backward");
}

/**
 * @brief Stops all motors.
 */
void run_stop()
{
  motor.setSpeed(0);  
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
}

/**
 * @brief Runs motors to turn the robot left.
 */
void run_lft()
{
  motor.setSpeed(-200);  
  motor2.setSpeed(-200);  
  motor3.setSpeed(200);  
  motor4.setSpeed(200);
  Serial.println("Left\n");
}

/**
 * @brief Runs motors to turn the robot right.
 */
void run_rgt()
{
  motor.setSpeed(200);  
  motor2.setSpeed(200);  
  motor3.setSpeed(-200);  
  motor4.setSpeed(-200);
  Serial.println("Right\n");
}

bool flag = false;

// Function to check for black line using line followers
void checkBlackLine() {
    // Read values from line follower sensors
    middleSensorValue = analogRead(MiddleLineFollower);
    rightSensorValue = analogRead(RightLineFollower);
    leftSensorValue = analogRead(LeftLineFollower);

    // Print out the sensor values
    Serial.print("Middle sensor value: ");
    Serial.println(middleSensorValue);
    Serial.print("Right sensor value: ");
    Serial.println(rightSensorValue);
    Serial.print("Left sensor value: ");
    Serial.println(leftSensorValue);

    /**
 * @brief Checks if any of the line follower sensors detect a black line and acts appropriately.
 */
    if ((middleSensorValue > blackLineThreshold  || rightSensorValue > blackLineThreshold || leftSensorValue > blackLineThreshold) && (flag == false)){
      flag == true;
      run_bwd();
      delay(1000);
      run_lft();
      delay(1000);
    }

    // Continue moving forward if no black line is detected
    run_fwd();
    flag == false;
}

/**
 * @brief Checks for objects using ultrasonic sensors and takes appropriate action.
 * @param trigPin Trigger pin for ultrasonic sensor.
 * @param echoPin Echo pin for ultrasonic sensor.
 * @param turnLeft Boolean to decide turning direction.
 */
void checkObj(int trigPin, int echoPin, bool turnLeft)
{
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate distance from echo time
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Check if object is within 40 cm
  if (distance < 40)
  { 
    // Turn based on which sensor detected the object
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
    // Continue moving forward if no object is detected
    run_fwd();
  }
}

/**
 * @brief Checks for objects using an IR sensor and takes appropriate action.
 */
void checkIR()
{
  // Read value from IR sensor
  int val = digitalRead(IRpin);
  
  // Check if the IR sensor detects an object
  if (val == LOW)
  {
    Serial.println("+++++++++++++++++IR Sensor: Object Detected++++++++++++++++++++++");
    run_stop();
    delay(100);
    run_bwd();
    delay(200);
    run_lft();
    delay(1000);
  }
  else
  {
    // Continue moving forward if no object is detected by the IR sensor
    run_fwd();
  }
}

/**
 * @brief Setup function, runs once at startup. Initializes pins and serial communication.
 */
void setup() {
    // Initialize sensor pins
    pinMode(MiddleLineFollower, INPUT);
    pinMode(RightLineFollower, INPUT);
    pinMode(LeftLineFollower, INPUT);

    pinMode(trigPinLeft, OUTPUT);
    pinMode(echoPinLeft, INPUT);
    pinMode(trigPinRight, OUTPUT);
    pinMode(echoPinRight, INPUT);

    pinMode(IRpin, INPUT);

    // Start serial communication
    Serial.begin(9600);

    // Register callback functions for timers
    lineTimer.register_callback(checkBlackLine);
    rightUSTimer.register_callback([]() { checkObj(trigPinLeft, echoPinLeft, false); });
    leftUSTimer.register_callback([]() { checkObj(trigPinRight, echoPinRight, true); });
    IRtimer.register_callback(checkIR);
}

/**
 * @brief Main loop function, runs repeatedly after setup. Executes sensor checks at specified intervals.
 */
void loop() {
    // Execute timer callbacks at specified intervals
    lineTimer.run(150);     // Check black line every 150ms
    rightUSTimer.run(150);  // Check right ultrasonic sensor every 150ms
    leftUSTimer.run(150);   // Check left ultrasonic sensor every 150ms
    IRtimer.run(100);       // Check IR sensor every 100ms
}

