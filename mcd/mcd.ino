#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
}

void loop() {
  oled.setFont(System5x7);
  oled.clear();
  oled.println("Hello");
  oled.print("World!");
  delay(2000);
}
