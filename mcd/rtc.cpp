#include "rtc.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

void initRTC() {
    // Initialize RTC
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        for(;;);
    }

    // Only set the RTC when it has lost power (e.g. first start or after battery change)
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

static void print2d(uint8_t v) {
    if (v < 10) {
        oled.print('0');
    }
    oled.print(v, DEC);
}

void oledPrintTime() {
    int cursorPos = getCursorPos(Time);
    if (cursorPos < 0) {
        return;
    }

    DateTime now = rtc.now();

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    // Print time
    oled.setCursor(0, cursorPos);
    print2d(now.hour());
    oled.print(':');
    print2d(now.minute());
    oled.print(':');
    print2d(now.second());
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
    oled.print('-');
    print2d(now.month());
    oled.print('-');
    print2d(now.day());
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