#include "mpu6050.h"

float AngleRoll, AnglePitch;
float AccX, AccY, AccZ;

float getAccel(int16_t raw) { return raw / 16384.0; } // MPU6050 scale factor for ±2g
float getGyro(int16_t raw) { return raw / 131.0; }    // MPU6050 scale factor for ±250°/s

void initMPU6050() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0); // Write 0 to PWR_MGMT_1 to wake up MPU6050
    Wire.endTransmission(true);
}

void readMPU6050(int16_t *accelX, int16_t *accelY, int16_t *accelZ, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 14, true);

    *accelX = (Wire.read() << 8 | Wire.read());
    *accelY = (Wire.read() << 8 | Wire.read());
    *accelZ = (Wire.read() << 8 | Wire.read());
    Wire.read(); Wire.read();  // Temperature (ignore)
    *gyroX = (Wire.read() << 8 | Wire.read());
    *gyroY = (Wire.read() << 8 | Wire.read());
    *gyroZ = (Wire.read() << 8 | Wire.read());
}

void oledPrintRollAngle() {
    int cursorPos = getCursorPos(RollAngle);
    if (cursorPos < 0) {
        return;
    }

    int16_t accelX, accelY, accelZ;
    int16_t gyroX, gyroY, gyroZ;

    readMPU6050(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

    // Convert to g and degrees/second
    float accelXg = getAccel(accelX);
    float accelYg = getAccel(accelY);
    float accelZg = getAccel(accelZ);
    float gyroXdps = getGyro(gyroX);

    float rollAcc = atan2(accelYg, accelZg) * 180 / M_PI;
    float dt = 0.01;

    float roll = kalmanFilter(rollAcc, gyroXdps, dt);

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    oled.setCursor(0, cursorPos);
    oled.print("Winkel: ");
    oled.print(roll);
}