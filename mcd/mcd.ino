#include "config.h"
#include "oled.h"
#include "rtc.h"
#include "temp.h"
#include "mpu6050.h"

int buttonState = LOW;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long previousRefreshTime = 0;

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(L2C_CLOCK_SPEED);

  initOLED();
  initMPU6050();
  initRTC();
  initTEMP();

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // Debounce Logic
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        handleButtonPress();
      }
    }
  }

  // Update Display Based on REFRESH_DELAY
  if (millis() - previousRefreshTime >= REFRESH_DELAY) {
    previousRefreshTime = millis();

    oled.clearDisplay();
    oledPrintTime();
    oledPrintDate();
    oledPrintWeekday();
    oledPrintTemp();
    oledPrintRollAngle();
    oled.display();
  }

  lastButtonState = reading;
}