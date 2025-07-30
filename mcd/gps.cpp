#include "gps.h"

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);

float lastSpeed = 0;
float totalSpeed = 0;
int speedSamples = 0;

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
        lastSpeed = gps.speed.kmph();

        oled.print("Speed: ");
        oled.print(String(lastSpeed, 1));
        oled.println("km/h");
    } else {
        oled.println("Speed: N/A");
    }
}

double lastLat = 0;
double lastLon = 0;
double totalDistance = 0;
bool firstFix = true;

void oledPrintDistanceTraveled() {
    int cursorPos = getCursorPos(Distance);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);

    if(gps.location.isUpdated()) {
        double currLat = gps.location.lat();
        double currLon = gps.location.lng();

        if(!firstFix) {
            double distance = TinyGPSPlus::distanceBetween(lastLat, lastLon, currLat, currLon);
            if(distance >= 1) {
                totalDistance += distance;
            }
        } else {
            firstFix = false;
        }

        lastLat = currLat;
        lastLon = currLon;

        oled.print("Distance Traveled: ");
        oled.print(String(totalDistance / 1000, 1));
        oled.print("km");
    } else {
        oled.print("Distance Traveled: N/A");
    }
}

void oledPrintAverageSpeed() {
    int cursorPos = getCursorPos(AverageSpeed);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);

    if(lastSpeed >= 1) {
        totalSpeed += lastSpeed;
        speedSamples++;
    }

    if(totalSpeed != 0) {
        oled.print("Average Speed: ");
        oled.print(String(totalSpeed / speedSamples, 1));
        oled.print("km/h")
    } else {
        oled.print("Average Speed: N/A");
    }
}

void oledPrintAltitude() {
    int cursorPos = getCursorPos(Altitude);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);
    oled.setCursor(0, cursorPos);

    if(gps.altitude.isUpdated()) {
        oled.print("Altitude: ");
        oled.print(gps.altitude.meters());
        oled.print("m");
    } else {
        oled.print("Altitude: N/A")
    }
}
