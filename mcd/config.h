#ifndef MCD_CONFIG_H
#define MCD_CONFIG_H

#define L2C_CLOCK_SPEED 400000L

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1             // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDRESS 0x3C

#define MAX_ELEMENTS_ON_SCREEN 4
#define TEXT_SIZE              1
#define TEXT_COLOR             SSD1306_WHITE
#define SPACE_BETWEEN_LINES    15

#define TEMP_DATA_PIN 5

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43
#define PWR_MGMT_1   0x6B

#define REFRESH_DELAY 1000

#define BUTTON_PIN     34
#define DEBOUNCE_DELAY 50

#define RX            16
#define TX            17
#define GPS_BAUD_RATE 9600

#endif //MCD_CONFIG_H
