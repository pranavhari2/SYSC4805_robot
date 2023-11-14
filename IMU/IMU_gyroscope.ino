#include <Wire.h>
#include <LSM6.h>
LSM6 imu;
char report[80];
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  if (!imu.init())
  {
  Serial.println("Failed to detect and initialize IMU!");
  while (1);
  }
  imu.enableDefault();
}

void loop()
{
  float Gx,Gy,Gz;
  imu.read();
  Gx = ((int16_t)imu.g.x) * 8.75/1000;
  Gy = ((int16_t)imu.g.y) * 8.75/1000;
  Gz = ((int16_t)imu.g.z) * 8.75/1000;
  Serial.println("Scaled Values of Gyroscope (+- 245dps)");
  snprintf(report, sizeof(report), "X-axis:%.3f Y-axis:%.3f Z-axis:%.3f",Gx, Gy,
  Gz);
  Serial.println(report);
  delay(500);
}