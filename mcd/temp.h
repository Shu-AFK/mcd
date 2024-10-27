#ifndef MCD_TEMP_H
#define MCD_TEMP_H

#include "config.h"
#include "oled.h"

#include <OneWire.h>
#include <DallasTemperature.h>

void initTEMP();
void oledPrintTemp();

#endif //MCD_TEMP_H
