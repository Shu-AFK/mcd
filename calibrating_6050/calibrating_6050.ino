#include <Wire.h>

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43
#define PWR_MGMT_1   0x6B

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C
  Wire.begin();
  Wire.setClock(100000L);

  // I2C Scanner
  Serial.println("Scanning for I2C devices...");
  bool deviceFound = false;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(addr, HEX);
      deviceFound = true;
      if (addr == MPU6050_ADDR) {
        Serial.println("MPU6050 found!");
      }
    }
    delay(10);
  }
  
  if (!deviceFound) {
    Serial.println("No I2C devices found. Check connections.");
  }
  
  // Initialize MPU6050 if found at the specified address
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);     // 0 wakes up the MPU6050
  if (Wire.endTransmission(true) != 0) {
    Serial.println("Failed to initialize MPU6050. Check wiring and power.");
  }
}

void loop() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true);

  if (Wire.available() == 14) {
    int16_t accelX = (Wire.read() << 8 | Wire.read());
    int16_t accelY = (Wire.read() << 8 | Wire.read());
    int16_t accelZ = (Wire.read() << 8 | Wire.read());
    Wire.read(); Wire.read();  // Skip temperature
    int16_t gyroX = (Wire.read() << 8 | Wire.read());
    int16_t gyroY = (Wire.read() << 8 | Wire.read());
    int16_t gyroZ = (Wire.read() << 8 | Wire.read());

    // Print values
    Serial.print("GyroX: ");
    Serial.println(gyroX);
    Serial.print("GyroY: ");
    Serial.println(gyroY);
    Serial.print("GyroZ: ");
    Serial.println(gyroZ);
  } else {
    Serial.println("Failed to read 14 bytes from MPU6050.");
  }

  delay(50);
}