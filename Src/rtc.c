#include "rtc.h"
#include "main.h"
#include "matrixDisplay.h"

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

void clockSetting(void) {
	while (mode == 2) { //variable are set by SET button in exti

		HALL_OFF;
		ALL_OFF;
		HAL_Delay(contacts);

		for (uint8_t i = 0; i < 6; i++) { //settings enter splash- blink all 3 times
			toggleAll();
			HAL_Delay(100);
		}

		while (mode == 2) { //while second to turn on splash(^) once.

			getTime(); //read actual hour
			uint8_t firstDigit = pullFirstDigit(hours); //variables using to store set digits
			uint8_t secondDigit = pullSecondDigit(hours);

			settingsLevel = 1;

			//HOURS<first digit
			while (settingsLevel == 1 && mode == 2) {

				showBinary(firstDigit); //show actual

				if (WAKE) { //add 1 to hours, when press wake
					if (firstDigit < 1) //only 1, becouse hourformat is 12h
						firstDigit++;
					else
						firstDigit = 0;
					HAL_Delay(contacts);
				}
				if (SET) { //go forward, when press set
					toggleAll(); //show user, that you go forward
					settingsLevel = 2; //go to step 2- second hour digit
					HAL_Delay(contacts);
				}
			} //end settings level 1

			//HOURS<second digit
			while (settingsLevel == 2 && mode == 2) {

				showBinary(secondDigit); //show actual
				//add 1 to hours, when press wake
				if (WAKE) {

					if (firstDigit == 1) {//0-1 range only if first digit equal 1.
						if (secondDigit < 1)
							secondDigit++;
						else
							secondDigit = 0;
						HAL_Delay(contacts);
					}

					if (firstDigit == 0) {//0-9 range only for first digit equal 0.
						if (secondDigit < 9)
							secondDigit++;
						else
							secondDigit = 0;
						HAL_Delay(contacts);
					}

				}
				if (SET) {
					toggleAll();			//show user, that you go forward
					settingsLevel = 3;	//go to step 3 - minutes first digit

					hours = firstDigit * 10;			//save first digit
					hours = hours + secondDigit;		//save second digit
					setTime();					//write time to rtc

					firstDigit = pullFirstDigit(minutes); //variables using to store set digits
					secondDigit = pullSecondDigit(minutes);

					HAL_Delay(contacts);

				}

			} //end settings level - HOURS

			//MINUTES<first digit
			while (settingsLevel == 3 && mode == 2) {

				showBinary(firstDigit); //show actual

				if (WAKE) { //add 1 to minutes when press wake
					if (firstDigit < 5) //0-5
						firstDigit++;
					else
						firstDigit = 0;
					HAL_Delay(contacts);
				}
				if (SET) { //go forward, when press set
					toggleAll(); //show user, that you go forward
					settingsLevel = 4; //go to step 4- second minutes digit
					HAL_Delay(contacts);
				}
			} //end settings level 3

			//MINUTES<second digit
			while (settingsLevel == 4 && mode == 2) {

				showBinary(secondDigit); //show actual
				//add 1 to minutes, when press wake
				if (WAKE) {

					if (secondDigit < 9)
						secondDigit++;
					else
						secondDigit = 0;
					HAL_Delay(contacts);

				}
				if (SET) {
					toggleAll();			//show user, that you go forward
					settingsLevel = 5;	//go to step 5 - seconds reset

					minutes = firstDigit * 10;			//save first digit
					minutes = minutes + secondDigit;	//save second digit
					setTime();							//write time to rtc

					firstDigit = 0;		//reset variables for minutes set
					secondDigit = 0;

					HAL_Delay(contacts);
				}
			} //end settings level - MINUTES

			//SECONDS
			while (settingsLevel == 5 && mode == 2) {

				getTime(); //for show blinking

				//blink at second change(pair-unpair)
				if ((seconds % 2) == 0) {
					ALL_ON;
				} else {
					ALL_OFF;
				}

				//reset seconds if press set

				if (SET) {
					toggleAll();			//show user, that you go forward
					settingsLevel = 0;	//turn off settings

					seconds = 0;	//save second to variable
					setTime();		//write seconds to rtc

					mode = 1;		//go to display mode
					workingCounter = 0;		//reset working counter

					HAL_Delay(contacts);
				}
			} //end settings level - SECONDS

		} //exit while mode 2 inside

	} //exit while mode 2 outside
}

