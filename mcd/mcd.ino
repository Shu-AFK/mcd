#include <Wire.h>
#include <Adafruit_GFX.h>            
#include <Adafruit_SSD1306.h>       
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128             // OLED display width, in pixels
#define SCREEN_HEIGHT 64             // OLED display height, in pixels
#define OLED_RESET    -1             // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDRESS   0x3C          // I2C address for the OLED display

#define TEMP_DATA_PIN 5              // Pin for the temperature sensor

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

OneWire oneWire(TEMP_DATA_PIN);
DallasTemperature sensor(&oneWire);

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

float AngleRoll, AnglePitch;
float AccX, AccY, AccZ;

void oledPrintTime();
void oledPrintTemp();
void oledPrintRollAngle();

void setupMPU6050();
float kalmanFilter(float newAngle, float newRate, float dt);
void readMPU6050(int16_t *accelX, int16_t *accelY, int16_t *accelZ, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ);

float getAccel(int16_t raw) { return raw / 16384.0; } // MPU6050 scale factor for ±2g
float getGyro(int16_t raw) { return raw / 131.0; }    // MPU6050 scale factor for ±250°/s

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000L);

  setupMPU6050();

  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  oled.clearDisplay();  // Clear the buffer
  oled.display();       // Show the cleared screen

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Uncomment to set the RTC to the current compile time (Only need to do once)
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Initialize temperature sensor
  sensor.begin();
}

void loop() {
  oled.clearDisplay();

  oledPrintTime();
  oledPrintTemp();

  oled.display();
  delay(1000);
}

void oledPrintTime() {
  DateTime now = rtc.now();

  oled.setTextSize(2);              // Set text size
  oled.setTextColor(SSD1306_WHITE); // Set text color

  // Print date
  oled.setCursor(0, 0);             // Start at top-left corner
  oled.print(now.year(), DEC);
  oled.print('/');
  oled.print(now.day(), DEC);
  oled.print('/');
  oled.print(now.month(), DEC);

  oled.setCursor(0, 20);
  oled.print("(");
  oled.print(daysOfTheWeek[now.dayOfTheWeek()]);
  oled.print(")");

  // Print time
  oled.setCursor(0, 40);           // Move cursor to a new line
  oled.print(now.hour(), DEC);
  oled.print(':');
  oled.print(now.minute(), DEC);
  oled.print(':');
  oled.print(now.second(), DEC);
}

void oledPrintTemp() {
  sensor.requestTemperatures();
  float tempC = sensor.getTempCByIndex(0);

  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 60);
  
  oled.print("Temp: ");
  oled.print(tempC);
  oled.print("C");
}

void setupMPU6050() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // 0 wakes up the MPU6050
  Wire.endTransmission(true);
}

void readMPU6050(int16_t *accelX, int16_t *accelY, int16_t *accelZ, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true);

  *accelX = (Wire.read() << 8 | Wire.read());
  *accelY = (Wire.read() << 8 | Wire.read());
  *accelZ = (Wire.read() << 8 | Wire.read());
  Wire.read(); Wire.read();  // Temperature (ignore)
  *gyroX = (Wire.read() << 8 | Wire.read());
  *gyroY = (Wire.read() << 8 | Wire.read());
  *gyroZ = (Wire.read() << 8 | Wire.read());
}

void oledPrintRollAngle() {
  int16_t accelX, accelY, accelZ;
  int16_t gyroX, gyroY, gyroZ;

  readMPU6050(accelX, accelY, accelZ, gyroX, gyroY, gyroZ);

  // Convert to g and degrees/second
  float accelXg = getAccel(accelX);
  float accelYg = getAccel(accelY);
  float accelZg = getAccel(accelZ);
  float gyroXdps = getGyro(gyroX);

  float rollAcc = atan2(accelYg, accelZg) * 180 / M_PI;
  float dt = 0.01;

  float roll = kalmanFilter(rollAcc, gyroXdps, dt);

  oled.setTextSize(2);              // Set text size
  oled.setTextColor(SSD1306_WHITE); // Set text color

  oled.setCursor(0, 0);
  oled.print("Winkel: ");
  oled.print(roll);
}

// Kalman filter variables
float Q_angle = 0.001f;             // Process noise variance for the accelerometer
float Q_bias = 0.003f;              // Process noise variance for the gyro bias
float R_measure = 0.03f;            // Measurement noise variance
float angle = 0.0f;                 // The angle calculated by the Kalman filter
float bias = 0.0f;                  // The gyro bias calculated by the Kalman filter
float P[2][2] = {{0, 0}, {0, 0}};   // Error covariance matrix
float rate;

float kalmanFilter(float newAngle, float newRate, float dt) {
  rate = newRate - bias;
  angle += dt * rate;

  // Updating the estimated error covariance ahead of time
  P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  // Measurement update
  float S = P[0][0] + R_measure; // Estimate error
  float K[2];                    // Kalman gain - This is a 2x1 vector
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;

  float y = newAngle - angle;
  angle += K[0] * y;
  bias += K[1] * y;

  // Updating the error covariance
  float P00_temp = P[0][0];
  float P01_temp = P[0][1];

  P[0][0] -= K[0] * P00_temp;
  P[0][1] -= K[0] * P01_temp;
  P[1][0] -= K[1] * P00_temp;
  P[1][1] -= K[1] * P01_temp;

  return angle;
}