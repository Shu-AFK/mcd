#ifndef MCD_RTC_H
#define MCD_RTC_H

#include "config.h"
#include "oled.h"

#include <RTClib.h>

extern RTC_DS3231 rtc;

void initRTC();
void oledPrintTime();
void oledPrintDate();
void oledPrintWeekday();

#endif //MCD_RTC_H
