#ifndef MCD_CONFIG_H
#define MCD_CONFIG_H

#define SCREEN_WIDTH  128             // OLED display width, in pixels
#define SCREEN_HEIGHT  64             // OLED display height, in pixels
#define OLED_RESET     -1             // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDRESS 0x3C             // I2C address for the OLED display

#define MAX_ELEMENTS_ON_SCREEN 3
#define TEXT_SIZE 10
#define TEXT_COLOR SSD1306_WHITE
#define SPACE_BETWEEN_LINES 20

#define TEMP_DATA_PIN 5

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

#define REFRESH_DELAY 1000

#define BUTTON_PIN 34

#endif //MCD_CONFIG_H
