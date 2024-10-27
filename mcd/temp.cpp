#include "temp.h"

OneWire oneWire(TEMP_DATA_PIN);
DallasTemperature sensor(&oneWire);

void initTEMP() {
    sensor.begin();
}

void oledPrintTemp() {
    int cursorPos = getCursorPos(Temperature);
    if (cursorPos < 0) {
        return;
    }

    oled.setTextSize(TEXT_SIZE);
    oled.setTextColor(TEXT_COLOR);

    sensor.requestTemperatures();
    float tempC = sensor.getTempCByIndex(0);

    oled.setCursor(0, cursorPos);

    oled.print("Temp: ");
    oled.print(tempC);
    oled.print("C");
}