#include "config.h"
#include "oled.h"
#include "rtc.h"
#include "temp.h"
#include "mpu6050.h"
#include "gps.h"

int skipButtonState = LOW;
int lastSkipButtonState = LOW;
unsigned long lastSkipDebounceTime = 0;

int startTimeButtonState = LOW;
int lastStartTimeButtonState = LOW;
unsigned long lastStartTimeDebounceTime = 0;

unsigned long lastDisplayRefreshTime = 0;

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(L2C_CLOCK_SPEED);

  initOLED();
  initMPU6050();
  initRTC();
  initTEMP();
  initGPS();

  pinMode(SKIP_BUTTON_PIN, INPUT);
  pinMode(START_TIME_BUTTON_PIN, INPUT);
}

void loop() {
  int skipReading = digitalRead(SKIP_BUTTON_PIN);

  // Debounce logic for the Skip Button
  if (skipReading != lastSkipButtonState) {
    lastSkipDebounceTime = millis();
  }

  if ((millis() - lastSkipDebounceTime) > DEBOUNCE_DELAY) {
    if (skipReading != skipButtonState) {
      skipButtonState = skipReading;

      if (skipButtonState == HIGH) {
        handleButtonPress();
      }
    }
  }

  lastSkipButtonState = skipReading;

  int startTimeReading = digitalRead(START_TIME_BUTTON_PIN);

  // Debounce logic for the Start Time Button
  if (startTimeReading != lastStartTimeButtonState) {
    lastStartTimeDebounceTime = millis();
  }

  if ((millis() - lastStartTimeDebounceTime) > DEBOUNCE_DELAY) {
    if (startTimeReading != startTimeButtonState) {
      startTimeButtonState = startTimeReading;

      if (startTimeButtonState == HIGH) {
        handleGPSTimeButtonPress();
      }
    }
  }

  lastStartTimeButtonState = startTimeReading;

  updateGPS();

  if (millis() - lastDisplayRefreshTime >= REFRESH_DELAY) {
    lastDisplayRefreshTime = millis();

    oled.clearDisplay();
    oledPrintTime();
    oledPrintDate();
    oledPrintWeekday();
    oledPrintTemp();
    oledPrintRollAngle();
    oledPrintSpeed();
    oledPrintDistanceTraveled();
    oledPrintAverageSpeed();
    oledPrintAltitude();
    oled.display();
  }
}
