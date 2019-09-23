#include "main.h"

#ifndef rtc_H
#define rtc_H

RTC_TimeTypeDef gDate;
RTC_TimeTypeDef gTime;

RTC_TimeTypeDef sDate;
RTC_TimeTypeDef sTime;

RTC_HandleTypeDef hrtc;

volatile uint8_t hours;
volatile uint8_t minutes;
volatile uint8_t seconds;
volatile uint32_t subseconds;

void getTime(void);
void setTime(void);




#endif
