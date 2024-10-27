#include "rtc.h"

RTC_DS3231 rtc;

void initRTC() {
    // Initialize RTC
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        for(;;);
    }

    // Uncomment to set the RTC to the current compile time (Only need to do once)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void oledPrintTime() {
    int cursorPos = getCursorPos(Date);
    if (cursorPos < 0) {
        return;
    }

    DateTime now = rtc.now();

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    // Print time
    oled.setCursor(0, cursorPos);
    oled.print(now.hour(), DEC);
    oled.print(':');
    oled.print(now.minute(), DEC);
    oled.print(':');
    oled.print(now.second(), DEC);
}

void oledPrintDate() {
    int cursorPos = getCursorPos(Date);
    if (cursorPos < 0) {
        return;
    }

    DateTime now = rtc.now();

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    oled.setCursor(0, cursorPos);
    oled.print(now.year(), DEC);
    oled.print('/');
    oled.print(now.day(), DEC);
    oled.print('/');
    oled.print(now.month(), DEC);
}

void oledPrintWeekday() {
    int cursorPos = getCursorPos(Weekday);
    if (cursorPos < 0) {
        return;
    }

    DateTime now = rtc.now();

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);


    oled.setCursor(0, cursorPos);
    oled.print("(");
    oled.print(daysOfTheWeek[now.dayOfTheWeek()]);
    oled.print(")");
}