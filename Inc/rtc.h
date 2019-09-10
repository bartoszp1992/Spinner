#include "main.h"

#ifndef rtc_H
#define rtc_H

RTC_TimeTypeDef gDate;
RTC_TimeTypeDef gTime;

RTC_TimeTypeDef sDate;
RTC_TimeTypeDef sTime;

RTC_HandleTypeDef hrtc;

uint8_t hours;
uint8_t minutes;
uint8_t seconds;
uint32_t subseconds;

void getTime(void);
void setTime(void);

void ccw(void);//counter-clockwise



#endif
