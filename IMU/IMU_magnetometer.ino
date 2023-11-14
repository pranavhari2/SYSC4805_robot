#include <Wire.h>
#include <LIS3MDL.h>
LIS3MDL mag;
LIS3MDL::vector<float> mag_min, mag_max, current;
char report[100];

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (!mag.init()) {
  Serial.println("Failed to detect and initialize magnetometer!");
  while (1);
  }

  mag.enableDefault();
  Serial.println("Calibrating for 10 Seconds. Roll, Pitch and Yaw to get high numbers!");
  unsigned long myTime = millis();

  while (millis() < myTime + 10000) {
    mag.read();
    mag_min.x = min(mag_min.x, mag.m.x); mag_min.y = min(mag_min.y, mag.m.y);
    mag_min.z = min(mag_min.z, mag.m.z); mag_max.x = max(mag_max.x, mag.m.x);
    mag_max.y = max(mag_max.y, mag.m.y); mag_max.z = max(mag_max.z, mag.m.z);
    snprintf(report, sizeof(report), "min: {%.0f, %.0f, %.0f} max: {%.0f, %.0f, %.0f}",
    mag_min.x, mag_min.y, mag_min.z, mag_max.x, mag_max.y, mag_max.z);
    Serial.println(report);
    delay(100);
  }
}

void loop() {
  mag.read();
  mag_min.x = min(mag_min.x, mag.m.x); mag_min.y = min(mag_min.y, mag.m.y);
  mag_min.z = min(mag_min.z, mag.m.z); mag_max.x = max(mag_max.x, mag.m.x);
  mag_max.y = max(mag_max.y, mag.m.y); mag_max.z = max(mag_max.z, mag.m.z);
  current.x = 2 * ((mag.m.x - mag_min.x) / (mag_max.x - mag_min.x)) - 1;
  current.y = 2 * ((mag.m.y - mag_min.y) / (mag_max.y - mag_min.y)) - 1;
  current.z = 2 * ((mag.m.z - mag_min.z) / (mag_max.z - mag_min.z)) - 1;
  snprintf(report, sizeof(report), "Mag: X-axis: %.3f, Y-axis: %.3f, Z-axis: %.3f .",
  current.x, current.y, current.z);
  Serial.println(report);
  delay(500);
}

