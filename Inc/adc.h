#include "main.h"

#ifndef ADC_H
#define ADC_H

uint16_t adcReading;
uint16_t adcValue;
uint16_t voltage;
uint16_t batteryState;//battery state in 0-60;

void adcInit(void);

void adcRead(void);

#endif
