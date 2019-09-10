#include "rtc.h"
#include "main.h"

void getTime() {

	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);

	hours = gTime.Hours;
	minutes = gTime.Minutes;
	seconds = gTime.Seconds;
	subseconds = gTime.SubSeconds;
}

void setTime() {

	sTime.Hours = hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;

	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);


}

void ccw(void) {//flips clock by a mirror. Use if motor runs CounterClockWise :)
	hours = 12 - hours;
	minutes = 60 - minutes;
	seconds = 60 - seconds;
}

