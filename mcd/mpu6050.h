#ifndef MCD_MPU6050_H
#define MCD_MPU6050_H

#include "config.h"
#include "oled.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

void initMPU6050();
void oledPrintRollAngle();

#endif //MCD_MPU6050_H
