#include "config.h"
#include "oled.h"
#include "rtc.h"
#include "temp.h"
#include "mpu6050.h"

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000L);

  initOLED();
  initMPU6050();
  initRTC();
  initTEMP();
}

void loop() {
  oled.clearDisplay();

  oledPrintTime();
  oledPrintDate();
  oledPrintWeekday();
  oledPrintTemp();
  oledPrintRollAngle();

  oled.display();
  delay(REFRESH_DELAY);
}