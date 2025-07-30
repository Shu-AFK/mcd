#ifndef MCD_GPS_H
#define MCD_GPS_H

#include "config.h"
#include "oled.h"
#include "rtc.h"

#include <TinyGPS++.h>
#include <HardwareSerial.h>

void initGPS();
void oledPrintSpeed();
void oledPrintDistanceTraveled();
void oledPrintAverageSpeed();
void oledPrintAltitude();
void updateGPS();

#endif //MCD_GPS_H
