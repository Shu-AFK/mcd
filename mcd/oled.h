#ifndef MCD_OLED_H
#define MCD_OLED_H

#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <stdint.h>

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

enum Features {
    Time,
    Date,
    Weekday,
    Temperature,
    RollAngle,
    COUNT, // This will hold the number of features
};

void initOLED();
void handleButtonPress();
int8_t getCursorPos(Features feature);

#endif //MCD_OLED_H
