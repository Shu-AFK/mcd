#ifndef MCD_RTC_H
#define MCD_RTC_H

#include "config.h"
#include "oled.h"

#include <RTClib.h>

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

void initRTC();
void oledPrintTime();
void oledPrintDate();
void oledPrintWeekday();

#endif //MCD_RTC_H
