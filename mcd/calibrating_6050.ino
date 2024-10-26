#include <Wire.h>

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000L);

  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // 0 wakes up the MPU6050
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true);

  int16_t accelX = (Wire.read() << 8 | Wire.read());
  int16_t accelY = (Wire.read() << 8 | Wire.read());
  int16_t accelZ = (Wire.read() << 8 | Wire.read());
  Wire.read(); Wire.read();  // Temperature (ignore)
  int16_t gyroX = (Wire.read() << 8 | Wire.read());
  int16_t gyroY = (Wire.read() << 8 | Wire.read());
  int16_t gyroZ = (Wire.read() << 8 | Wire.read());

  Serial.print("GyroX: ");
  Serial.println(gyroX);
  Serial.print("GyroY: ");
  Serial.println(gyroY);
  Serial.print("GyroZ: ");
  Serial.println(gyroZ);

  delay(50);
}