#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 mpu;

void setup() {
    Wire.begin();
    Wire.setClock(400000);
    
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    Serial.println(F("Initializing MPU6050..."));
    mpu.initialize();
    
    Serial.println(F("Testing connection..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    
    Serial.println(F("\nSend any character to calibrate and show offsets..."));
    while (Serial.available() && Serial.read()); // Clear buffer
}

void loop() {
    if (Serial.available() > 0) {
        while (Serial.available() && Serial.read());
        
        Serial.println(F("\nCalibrating sensors (keep device stable)..."));
        
        // Perform calibration
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        
        // Get and print offsets
        Serial.println(F("\nCalculated Offsets:"));
        Serial.print(F("Accel X/Y/Z: "));
        Serial.print(mpu.getXAccelOffset()); Serial.print("\t");
        Serial.print(mpu.getYAccelOffset()); Serial.print("\t");
        Serial.println(mpu.getZAccelOffset());
        
        Serial.print(F("Gyro X/Y/Z: "));
        Serial.print(mpu.getXGyroOffset()); Serial.print("\t");
        Serial.print(mpu.getYGyroOffset()); Serial.print("\t");
        Serial.println(mpu.getZGyroOffset());
        
        Serial.println(F("\nSend another character to recalibrate"));
    }
}