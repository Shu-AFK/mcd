#include <Wire.h>
#include <Adafruit_GFX.h>            
#include <Adafruit_SSD1306.h>       
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128             // OLED display width, in pixels
#define SCREEN_HEIGHT 64             // OLED display height, in pixels
#define OLED_RESET    -1             // Reset pin # (or -1 if sharing Arduino reset pin)
#define I2C_ADDRESS   0x3C           // I2C address for the OLED display
#define TEMP_DATA_PIN 5              // Pin for the temperature sensor

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

OneWire oneWire(TEMP_DATA_PIN);
DallasTemperature sensor(&oneWire);

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

void oledPrintTime();
void oledPrintTemp();

void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000L);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS)) {
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