#include "matrixDisplay.h"
#include "main.h"
#include "rtc.h"
#include "adc.h"

void matrixDisplayInit(void) {
	workingTime = 12; //TIM2 cycles. time of watch spinning or run in settings mode/20

	workingCounter = workingTime; //sleep mode as default. When equals, sync interrupt turns on mode 0(stop mode)
	mode = 0; //sleep mode as default. As a supplement to ^. Becouse these variables are dependent.

	weakCounter = 0;
	weakTime = 4;//8


	minRpt = 10; //minimum rotating speed- turns on time showing if reached.//20
	settingsLevel = 0; //default settings level are 0, becouse settings are turned off by default
	contacts = 200; //switches contacts vibrations

	HAL_TIM_Base_Start_IT(&htim2);
	//^turns on timer2 used for sync interrupts
}

//async interrupts- generated by opto.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == GPIO_PIN_1) { //opto interrupter

		rotatesCounter++; //add pulse
		startFlag = 1; //start display cycle

	}

	if (GPIO_Pin == GPIO_PIN_3) { //wake button
		workingCounter = 0; //reset working time counter. mode will be set to 1 below

		if (mode == 0) {
			mode = 1; //set to 1- display mode. but only from 0- stop mode. It can't turns on display mode from settings(2)
			SystemClock_Config();		//set clock after wakeup
			rpt = 0;		//set start rpt as 0
			weakCounter = 0;		//reset weak counter
		}

	}
	if (GPIO_Pin == GPIO_PIN_4) { //set button
		workingCounter = 0; //set also reset working counter- becouse of settings
		if (mode == 0) {
			mode = 2; //turns on settings mode- only from stop. It cant interfere in settings mode and with ONDEMAND/FORCE mode select
			SystemClock_Config(); //set clock after wakeup
			weakCounter = 0; //reset weak counter
		}

	}
}

//sync interrupts- every second
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM2) { //each second

		if (batteryState < 10)
			forceMode = 0;

		//column time measurement
		rpt = rotatesCounter;
		rotatesCounter = 0; //reset rotates counter
		if (rpt < minRpt) {
			rotateTime = (1000000 / rpt);
			columnTime = (rotateTime / 60);

			if (mode == 1) { //increment weak Counter only in running mode
				weakCounter++; //if rpt < normal, start counting weakTime
				if (weakCounter > weakTime) {
					mode = 0;
					workingCounter = workingTime;
				}
			}

		} else {
			weakCounter = 0; //reset counter if rpt is above normal.
		}
		//^column time is counting only in start sequence. If rpt reaches minimum, column time is only corrected inside matrixDisplay()

		//counting running time(1 - display mode)
		if (workingCounter < workingTime) {
			if (forceMode == 0 || mode == 2)
				workingCounter++;
			//^increment working counter only if forceMode are off, or if forcemode is on and
		} else {
			mode = 0;
			//^if counts to working time, turns on mode 0 - stop mode.
		}

	}

}

//experimental 1us delay
void delayUs(uint32_t delay) {

	if (delay > 200000)
		delay = 0;

	volatile uint32_t delayUs = delay * 0.36;
	//volatile uint32_t delayUs = delay / 9;

	for (uint32_t i = 0; i < delayUs; i++)
		;
}

void matrixWriteState() {
	for (int i = 0; i < batteryState; i++) {
		screenMatrix[6][i] = 1;
	}
}

void matrixClearState() {
	for (int i = 0; i < 60; i++) {
		screenMatrix[6][i] = 0;
	}
}

//writing pointers to matrix
void matrixWriteTime(uint8_t hour, uint8_t minute, uint8_t second,
		uint8_t level) {

	for (uint8_t i = 1; i <= 2; i++) {
		screenMatrix[i][second] = level;
	}
	for (uint8_t i = 2; i <= 6; i++) {
		screenMatrix[i][minute] = level;
	}

	for (uint8_t i = 4; i <= 6; i++) {

		screenMatrix[i][hour * 5 + (minute / 10)] = level; //clockwise
		screenMatrix[i][hour * 5 + (minute / 10) + 1] = level;
	}
}

//writing hour markers to matrix
void matrixWriteMarkers() { //write hours markers to matrix

	//every 5 minutes
	for (uint8_t i = 0; i <= 55; i = i + 5) {

		screenMatrix[0][i] = 1;

	}

	//every 3 hours
	for (uint8_t i = 0; i <= 55; i = i + 15) {

		screenMatrix[1][i] = 1;

	}
}

//displaying matrix
void matrixDisplayCcw() {
	if (startFlag == 1) {

		getTime();

		matrixWriteMarkers();
		matrixWriteTime(hours, minutes, seconds, 1);
		adcRead();
		matrixWriteState();

		startFlag = 0;

		ALL_OFF
		;
		for (int i = 59; i >= 0; i--) { //for each from 60 column repeat:(i are column number)

			for (int j = 0; j <= 6; j++) { //for each pixel repeat:(j are row number)

				if (screenMatrix[j][i] == 1) { //in case of 1 in matrix pixel, turn on LED

					turnOn(j);

				} //end if
				if (startFlag == 1) { //if EXTI occurs

					//columnTime--; //decrease columnTime- means, that columnTime is too long.
					columnTime = columnTime - 100 / rpt;
					break; //and exit loop. Will be started in next run.
				}
				delayUs(columnTime);

			} //end for

			ALL_OFF
			; //turn off all LEDs

		} //end for

		matrixWriteTime(hours, minutes, seconds, 0); //reload full array takes too log time
		matrixClearState();
	} else {
		columnTime++;
		//^if startFlag isn't on instantly after display cycle means that column time are too short.
	}
} //end function

void matrixSplash(uint16_t delay) {

	HAL_Delay(delay);
	turnOn(6);
	HAL_Delay(delay);
	turnOn(5);
	HAL_Delay(delay);
	turnOn(4);
	HAL_Delay(delay);
	turnOn(3);
	turnOff(6);
	HAL_Delay(delay);
	turnOn(2);
	turnOff(5);
	HAL_Delay(delay);
	turnOn(1);
	turnOff(4);
	HAL_Delay(delay);
	turnOn(0);
	turnOff(3);
	HAL_Delay(delay);
	turnOff(2);
	HAL_Delay(delay);
	turnOff(1);
	HAL_Delay(delay);
	turnOff(0);

}

//turn on LED with number in argument
void turnOn(int led) {

	switch (led) {

	case 0:
		L0_ON;
		break;

	case 1:
		L1_ON;
		break;

	case 2:
		L2_ON;
		break;

	case 3:
		L3_ON;
		break;

	case 4:
		L4_ON;
		break;

	case 5:
		L5_ON;
		break;

	case 6:
		L6_ON;
		break;

	}
}

void turnOff(int led) {

	switch (led) {

	case 0:
		L0_OFF;
		break;

	case 1:
		L1_OFF;
		break;

	case 2:
		L2_OFF;
		break;

	case 3:
		L3_OFF;
		break;

	case 4:
		L4_OFF;
		break;

	case 5:
		L5_OFF;
		break;

	case 6:
		L6_OFF;
		break;

	}
}

//toggle all LEDs
void toggleAll() {
	HAL_GPIO_TogglePin(L0_GPIO_Port, L0_Pin);
	HAL_GPIO_TogglePin(L1_GPIO_Port, L1_Pin);
	HAL_GPIO_TogglePin(L2_GPIO_Port, L2_Pin);
	HAL_GPIO_TogglePin(L3_GPIO_Port, L3_Pin);
	HAL_GPIO_TogglePin(L4_GPIO_Port, L4_Pin);
	HAL_GPIO_TogglePin(L5_GPIO_Port, L5_Pin);
	HAL_GPIO_TogglePin(L6_GPIO_Port, L6_Pin);
}

uint8_t pullFirstDigit(uint8_t number) {

	return number / 10;
}

uint8_t pullSecondDigit(uint8_t number) {

	uint8_t firstDigit = number / 10;
	return number - (firstDigit * 10);
}

//show binary digit- for settings mode
void showBinary(uint8_t number) {

	ALL_OFF
	;
	switch (number) {

	case 1:
		turnOn(0);
		break;

	case 2:
		turnOn(1);
		break;

	case 3:
		turnOn(0);
		turnOn(1);
		break;

	case 4:
		turnOn(2);
		break;

	case 5:
		turnOn(2);
		turnOn(0);
		break;

	case 6:
		turnOn(2);
		turnOn(1);
		break;

	case 7:
		turnOn(2);
		turnOn(1);
		turnOn(0);
		break;

	case 8:
		turnOn(3);
		break;

	case 9:
		turnOn(3);
		turnOn(0);
		break;
	}
}
