/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example shows how to drive a motor using the PWM and DIR pins.
 * This example only shows how to drive a single motor for simplicity.
 * For dual channel motor driver, both channel work the same way.
 * 
 * 
 * CONNECTIONS:
 * 
 * Arduino D3  - Motor Driver PWM Input
 * Arduino D4  - Motor Driver DIR Input
 * Arduino GND - Motor Driver GND
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

 #include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor(PWM_DIR, 2, 9);  // PWM = Pin 2, DIR = Pin 9  
CytronMD motor2(PWM_DIR, 4, 3);  // PWM = Pin 4, DIR = Pin 3
CytronMD motor3(PWM_DIR, 5, 6);  // PWM = Pin 5, DIR = Pin 6   
CytronMD motor4(PWM_DIR, 8, 7);  // PWM = Pin 8, DIR = Pin 7


void run_motor(CytronMD motor, int number){
  motor.setSpeed(128);  // Run forward at 50% speed.
  delay(1000);
  Serial.print("Move forward 50%");
  Serial.println();
  Serial.print(number);
  Serial.println();
  
  motor.setSpeed(255);  // Run forward at full speed.
  delay(1000);
  Serial.print("Move forward full speed");
  Serial.println();

  motor.setSpeed(0);    // Stop.
  delay(1000);
  Serial.print("Stop");
  Serial.println();

  motor.setSpeed(-128);  // Run backward at 50% speed.
  delay(1000);
  Serial.print("Move backwards 50%");
  Serial.println();
  
  motor.setSpeed(-255);  // Run backward at full speed.
  delay(1000);
  Serial.print("Move backward full speed");
  Serial.println();

  motor.setSpeed(0);    // Stop.
  delay(1000);
  Serial.print("Stop");
  Serial.println();
}

// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(9600);
}

// The loop routine runs over and over again forever.
void loop() {
  int number = 1;
  run_motor(motor, number);
  number = 2;
  run_motor(motor2, number);
  number = 3;
  run_motor(motor3, number);
  number = 4;
  run_motor(motor4, number);
}
