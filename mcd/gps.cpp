#include "gps.h"

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);

DateTime travelTimeStart;
DateTime travelTimeEnd;
bool currentlyDriving = false;

void updateGPS() {
    while (GPSSerial.available() > 0) {
        gps.encode(GPSSerial.read());
    }
}

void initGPS() {
    GPSSerial.begin(GPS_BAUD_RATE, SERIAL_8N1, RX, TX);
}

void oledPrintSpeed() {
    int cursorPos = getCursorPos(Speed);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);

    if (gps.speed.isUpdated()) {
        oled.print("Speed: ");
        oled.print(gps.speed.kmph());
        oled.println(" km/h");
    } else {
        oled.println("Speed: N/A");
    }
}

void handleGPSTimeButtonPress() {
  currentlyDriving = !currentlyDriving;

  if (currentlyDriving) {
    travelTimeStart = rtc.now();
  } else {
    travelTimeEnd = rtc.now();
  }
}

// TODO: Implement but the start time is needed

void oledPrintDistanceTraveled() {
    int cursorPos = getCursorPos(Distance);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);
}

void oledPrintAverageSpeed() {
    int cursorPos = getCursorPos(AverageSpeed);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);
}

void oledPrintAltitude() {
    int cursorPos = getCursorPos(Altitude);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);
}