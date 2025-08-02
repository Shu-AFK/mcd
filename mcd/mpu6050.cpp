#include "mpu6050.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <math.h>

MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;
uint8_t fifoBuffer[64]; 

// orientation/motion vars
Quaternion q;
VectorFloat gravity;
float ypr[3];

volatile bool mpuInterrupt = false;
void dmpDataReady() {
    mpuInterrupt = true;
}

void initMPU6050() {
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    Serial.println(F("[MPU6050] Initializing DMP..."));

    mpu.setXGyroOffset(X_GYRO_OFF);
    mpu.setYGyroOffset(Y_GYRO_OFF);
    mpu.setZGyroOffset(Z_GYRO_OFF);
    mpu.setXAccelOffset(X_ACC_OFF);
    mpu.setYAccelOffset(Y_ACC_OFF);
    mpu.setZAccelOffset(Z_ACC_OFF);

    uint8_t devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        dmpReady = true;
        Serial.println(F("[MPU6050] DMP ready"));
    } else {
        Serial.print(F("[MPU6050] DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void readMPU6050() {
    if (!dmpReady) return;

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
}

void oledPrintRollAngle() {
    int cursorPos = getCursorPos(RollAngle);
    if (cursorPos < 0) return;

    readMPU6050();

    float lean_angle = ypr[2] * 180.0 / M_PI; // Roll in degrees

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    oled.setCursor(0, cursorPos);
    oled.print("Winkel: ");
    oled.print(lean_angle, 1);
    oled.print("°");
}