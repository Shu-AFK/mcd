/* 
 * Libraries used:
 *   - SSD1306Ascii for the OLED display
 *   - RTClib for the DS3231RTC
 */

#include <Wire.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "RTClib.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#define I2C_ADDRESS 0x3C
#define TEMP_DATA_PIN 5

SSD1306AsciiWire oled;
RTC_DS3231 rtc;

OneWire oneWire(TEMP_DATA_PIN);	
DallasTemperature sensor(&oneWire);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000L);

  Serial.println("Starting OLED the display...");
  oled.begin(&Adafruit128x64, I2C_ADDRESS);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  Serial.println("Setting the time...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("Starting temperature sensor...");
  sensor.begin();
}

void loop() {
  oled.setFont(fixed_bold10x15);
  oled.clear();
  oled.println("Hello");
  oled.print("World!");

  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.println();

  sensor.requestTemperatures();
  Serial.print("Temperature: ");
  Serial.print(sensor.getTempCByIndex(0));
  Serial.print("℃ | ");

  Serial.print((sensor.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("℉");

  delay(3000);
}
