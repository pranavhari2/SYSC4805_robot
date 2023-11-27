#include "Simpletimer.h"
#include "CytronMotorDriver.h"
// Define statements for the motor driver
// Todo: Change the pin numbers 
#define MiddleLineFollower A7
#define RightLineFollower A6
#define LeftLineFollower A5

#define trigPinRight 10
#define echoPinRight 13
#define trigPinLeft 12
#define echoPinLeft 11

CytronMD motor(PWM_DIR, 2, 9);
CytronMD motor3(PWM_DIR, 5, 6); 
CytronMD motor2(PWM_DIR, 4, 3);
CytronMD motor4(PWM_DIR, 8, 7);

Simpletimer timer{};
Simpletimer timer2{};
Simpletimer timer3{};

void setup() {

  pinMode(MiddleLineFollower, INPUT);
  pinMode(RightLineFollower, INPUT);
  pinMode(LeftLineFollower, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  Serial.begin(74880);

  timer.register_callback(checkBlackLine);
  timer2.register_callback([]() { checkObj(trigPinLeft, echoPinLeft, false); });
  timer3.register_callback([]() { checkObj(trigPinRight, echoPinRight, true); });
}



void mock_runbwd(){
  Serial.println("Backward");
}

void mock_runfwd(){
  Serial.println("Forward");
}


void run_fwd()
{
  motor.setSpeed(128);  
  motor2.setSpeed(128);  
  motor3.setSpeed(128);  
  motor4.setSpeed(128);  
  Serial.println("Forward");
}

void run_bwd(){
  motor.setSpeed(-128);  
  motor2.setSpeed(-128);  
  motor3.setSpeed(-128);  
  motor4.setSpeed(-128);
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
  motor.setSpeed(-128);  
  motor2.setSpeed(-128);  
  motor3.setSpeed(128);  
  motor4.setSpeed(128);
  Serial.println("Left\n");
}
void run_rgt()
{
  motor.setSpeed(128);  
  motor2.setSpeed(128);  
  motor3.setSpeed(-128);  
  motor4.setSpeed(-128);
  Serial.println("Right\n");
}


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

void checkObj(int trigPin, int echoPin, bool turnLeft)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  
  if (distance < 15)
  { 
    if (turnLeft) 
    {
      Serial.println("Right Sensor: Object Detected");
      run_stop();
      delay(1000);
      run_lft();
      delay(1000);
      run_fwd();
    } 
    else 
    {
      Serial.println("Left Sensor: Object Detected");
      run_stop();
      delay(1000);
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

void loop() {
  //timer.run(250);
  timer2.run(250);
  timer3.run(250);
}