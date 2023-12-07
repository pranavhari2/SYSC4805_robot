#include <Wire.h>
#include <LSM6.h>
LSM6 imu;
char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  if (!imu.init()){
  Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  float Ax,Ay,Az;                                                               
  imu.read();
  Ax = ((int16_t)imu.a.x)*0.061/1000;
  Ay = ((int16_t)imu.a.y)*0.061/1000;
  Az = ((int16_t)imu.a.z)*0.061/1000;
  Serial.println("Scaled Values of Acceleration (+-2g))");
  snprintf(report, sizeof(report), "X-axis:%.3f Y-axis:%.3f Z-axis:%.3f", Ax, Ay, Az);
  Serial.println(report);
  delay(500);
}

