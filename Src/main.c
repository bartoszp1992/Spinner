/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 * Bart's phantom watch vMilestone1
 *
 * PA1- added function for testing display, functions in separated file
 * PA2- more code comments, added function for display pointers
 * MS1- working clock, correct direct(clockwise :) )
 * MS2- working clock, working synchro
 * v0.1 pre alpha- ondemand start- not tested
 * v0.2 PA2 - tested on synchro board, working. Problem with synchro.
 * v0.2 PA3 - low power modes- first attempt
 * v0.3 PA4 - migrate to L041F6
 * v0.4 MS3 - milestone3:
 * 			setting time
 * 			low power modes
 * 			removed blinking
 *
 * v0.5
 * 			ondemand/force select
 *
 * v0.55
 * 			correct clock setting
 * 			hour pointer fix(now is dependent of minutes)
 *
 * v0.56
 * 			now columnTime are counted by sync interrupt only on start. If working, columnTime are only corrected in matrixDisplay() function.
 * 			added subsecond marker
 * 			sync interrupt time changed for 1 sec
 * 			added busy flag(but it isnt in use).
 * 			rpt is set to 0 after wakeup.

 * v0.57
 * 			fixed freeze bug on the sun.
 *
 * v0.58
 * 			shorted working time.
 *
 * v0.59
 * 			prepared for Synchro v0.2 board- disabled pullup for exti pin.
 * 			changed for hall sensor
 *
 *v0.6
 *			corrected counter clockwise mode- now just the matrix is shown swapped.
 *
 *v0.7
 *			added new matrixDisplah.c file for reverse columnTime counting.
 *
 *v0.71
 *			new idea for columnTimeCounting
 *
 *v0.72
 *			return to old columnTime counting
 *
 *v0.73
 *			auto sleep also in settings mode
 *			clock will not be reset if you enter settings mode :)
 *
 *v0.74
 *			added weak time- if rpt is below limit for selected time - clock will go to sleep
 *
 *v0.8
 *			batterystate measurement + force mode are now disabled, if state <10
 *
 *todo:
 *shaky screen- caused by matrixWriteTime(); Move this function to TIM2 interrupt.
 *counting columnTime is not enough presice. Where's the problem?
 *ADD ADC, temperature and battery state measurement
 *make secure- second hour digit must be set to - when first was set above 0.


 *short pointer at 00:00

 currents:
 stop mode- 64uA

 Battery lifetime:
 cells: 2x lipo 120mAh
 30sec runs: 180
 idle: 150 days
 force working: 1h30'
 charging: 250mA / 1h
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "matrixDisplay.h"
#include "rtc.h"
#include "adc.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_RTC_Init();
	MX_TIM2_Init();
	MX_ADC_Init();
	/* USER CODE BEGIN 2 */
	matrixDisplayInit();
	adcInit();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		//SECTION 0 - display mode

		if (mode == 1) {
			HALL_ON; //turn on interrupter ant vent
			if (rpt >= minRpt) { //if rpt are enough, run display

				getTime();

				matrixWriteMarkers();
				matrixWriteTime(hours, minutes, seconds, 1);
				adcRead();
				matrixWriteState();

				matrixDisplayCcw();

				matrixWriteTime(hours, minutes, seconds, 0); //reload full array takes too log time
				matrixClearState();

			} else { //if watch still accelerates, show splash
				matrixSplash(50);
			}

		}

		if (mode == 0) { //this mode are set by sync interrupt, when workingCounter are bigger than set(when displaying time is up).
			HALL_OFF; //turn off interrupter and vent
			ALL_OFF
			;
			HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI); //go to stop mode :)
		}

		//SECTION 1 - //force/ondemand mode select - press SET and WAKE parallel
		if (WAKE) {

			HAL_Delay(contacts);

			if (SET && WAKE) {
				for (uint8_t i = 0; i < 6; i++) { //settings enter splash- blink all 3 times
					toggleAll();
					HAL_Delay(100);
				}

				if (forceMode == 1) {
					forceMode = 0;
				} else if (forceMode == 0) {
					forceMode = 1;
				}

				HAL_Delay(contacts);
			}
		}

		//SECTION 2 - CLOCK SETTING //press SET only
		while (mode == 2) { //variable are set by SET button in exti

			HALL_OFF;
			ALL_OFF
			;
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
						ALL_ON
						;
					} else {
						ALL_OFF
						;
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

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC_Init(void) {

	/* USER CODE BEGIN ADC_Init 0 */

	/* USER CODE END ADC_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC_Init 1 */

	/* USER CODE END ADC_Init 1 */
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc.Instance = ADC1;
	hadc.Init.OversamplingMode = DISABLE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
	hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.LowPowerFrequencyMode = DISABLE;
	hadc.Init.LowPowerAutoPowerOff = DISABLE;
	if (HAL_ADC_Init(&hadc) != HAL_OK) {
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel to be converted.
	 */
	sConfig.Channel = ADC_CHANNEL_5;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC_Init 2 */

	/* USER CODE END ADC_Init 2 */

}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void) {

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */
	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_12;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 1;
	sTime.Minutes = 30;
	sTime.Seconds = 40;
	sTime.TimeFormat = RTC_HOURFORMAT12_AM;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 1;
	sDate.Year = 0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 3999;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 7999;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			HALL_Pin | L0_Pin | L1_Pin | L3_Pin | L4_Pin | L5_Pin | L6_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : HALL_Pin L0_Pin L1_Pin L3_Pin
	 L4_Pin L5_Pin L6_Pin */
	GPIO_InitStruct.Pin = HALL_Pin | L0_Pin | L1_Pin | L3_Pin | L4_Pin | L5_Pin
			| L6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : EXTI_Pin */
	GPIO_InitStruct.Pin = EXTI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(EXTI_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : WAKE_Pin SET_Pin */
	GPIO_InitStruct.Pin = WAKE_Pin | SET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : L2_Pin */
	GPIO_InitStruct.Pin = L2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(L2_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

	HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
