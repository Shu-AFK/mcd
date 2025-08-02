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

#define SKIP_BUTTON_PIN       34
#define START_TIME_BUTTON_PIN 23
#define DEBOUNCE_DELAY        50

#define RX_PIN        16
#define TX_PIN        17
#define GPS_BAUD_RATE 9600

// Change these to the offsets got by calibration
#define X_GYRO_OFF 0
#define Y_GYRO_OFF 0
#define Z_GYRO_OFF 0
#define X_ACC_OFF 0
#define Y_ACC_OFF 0
#define Z_ACC_OFF 0

#define INTERRUPT_PIN 2

#endif //MCD_CONFIG_H
