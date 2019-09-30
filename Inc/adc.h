#include "main.h"

#ifndef ADC_H
#define ADC_H

void adcInit(void);

void adcConvert(void);

uint16_t adcReading[2];
uint16_t voltage;
uint16_t batteryState;//battery state in 0-60;


#endif
