#include "config.h"
#include "oled.h"
#include "rtc.h"
#include "temp.h"
#include "mpu6050.h"

int buttonState = 0;

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000L);

  initOLED();
  initMPU6050();
  initRTC();
  initTEMP();

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
      handleButtonPress();
  }

  oled.clearDisplay();

  oledPrintTime();
  oledPrintDate();
  oledPrintWeekday();
  oledPrintTemp();
  oledPrintRollAngle();

  oled.display();
  delay(REFRESH_DELAY);
}