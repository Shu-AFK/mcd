#include "oled.h"

#include <array>

std::array<Features, MAX_ELEMENTS_ON_SCREEN> displayed;

void initOLED() {
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("SSD1306 allocation failed");
        for(;;);
    }

    oled.clearDisplay();  // Clear the buffer
    oled.display();       // Show the cleared screen

    for(int i = 0; i < MAX_ELEMENTS_ON_SCREEN; i++) {
        displayed[i] = static_cast<Features>(i);
    }
}

void handleButtonPress() {
    for (int i = 0; i < MAX_ELEMENTS_ON_SCREEN; i++) {
        if (displayed[i] == static_cast<Features>(static_cast<int>(COUNT) - 1)) {
            displayed[i] = static_cast<Features>(0);
        } else {
            displayed[i] = static_cast<Features>(static_cast<int>(displayed[i]) + 1);
        }
    }
}

int8_t getCursorPos(Features feature) {
    for (int i = 0; i < MAX_ELEMENTS_ON_SCREEN; i++) {
        if (displayed[i] == feature) {
            return i * SPACE_BETWEEN_LINES;
        }
    }

    return -1;
}