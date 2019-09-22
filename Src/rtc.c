#include "rtc.h"
#include "main.h"

void getTime() {

	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);

	hours = gTime.Hours;
	minutes = gTime.Minutes;
	seconds = gTime.Seconds;
//	subseconds = (gTime.SubSeconds*10)/43;// subsecond from RTC is 1/255 of second(becouse of RTC sync predivider)
//	//^ 1/60 of second will be RTC subsecond divided by 4.25
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

