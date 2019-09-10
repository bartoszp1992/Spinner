#include "main.h"//nag��wek u�ywa funkcji HALa
//#include "stm32f0xx_hal.h"

#ifndef matrixDisplay_H
#define matrixDisplay_H

TIM_HandleTypeDef htim2;

//counting, synchro and times
volatile uint8_t startFlag;//fot start alway in the same place
volatile uint8_t busyFlag;
volatile uint32_t rotatesCounter;
volatile uint32_t rpt;// rotates per time
volatile uint32_t rotateTime;
volatile uint32_t columnTime;

//delays
uint8_t contacts;


//working modes
volatile uint8_t mode;//0- sleep, 1-ondemand/force, 2-setting
uint8_t forceMode;
volatile uint8_t workingCounter;
volatile uint8_t workingTime;//time of spinning in ondemand mode
volatile uint8_t minRpt;//minimum rpt
uint8_t settingsLevel;//


/* 0- none
 * HOURS
 * 1- first digit
 * 2- second digit
 * MINUTES
 * 3- first digit
 * 4- second digit
 * SECONDS
 * 5- reset
 */

uint8_t screenMatrix[7][60];//variable to store matrix content.

//matrix LEDs
#define L0_ON HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, 1)
#define L1_ON HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, 1)
#define L2_ON HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, 1)
#define L3_ON HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, 1)
#define L4_ON HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, 1)
#define L5_ON HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, 1)
#define L6_ON HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, 1)

#define L0_OFF HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, 0)
#define L1_OFF HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, 0)
#define L2_OFF HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, 0)
#define L3_OFF HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, 0)
#define L4_OFF HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, 0)
#define L5_OFF HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, 0)
#define L6_OFF HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, 0)

#define ALL_OFF L0_OFF; L1_OFF; L2_OFF; L3_OFF; L4_OFF; L5_OFF; L6_OFF
#define ALL_ON L0_ON; L1_ON; L2_ON; L3_ON; L4_ON; L5_ON; L6_ON

//opto interrupter and motor
#define OPTO_ON HAL_GPIO_WritePin(OPTO_GPIO_Port, OPTO_Pin, 1)
#define OPTO_OFF HAL_GPIO_WritePin(OPTO_GPIO_Port, OPTO_Pin, 0)

//buttons
#define WAKE HAL_GPIO_ReadPin(WAKE_GPIO_Port, WAKE_Pin)==0
#define SET HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin)==0

//matrix functions
void matrixWriteMarkers(void);
void matrixWriteTime(uint8_t hour, uint8_t minute, uint8_t second, uint32_t subsecond, uint8_t state);
void matrixDisplay(void);
void matrixDisplayInit(void);
void matrixSplash(uint16_t delay);

//led functions
void turnOn(int led);
void turnOff(int led);
void toggleAll(void);

//delay functions
void delayUs(uint32_t delay);

//others
void showBinary(uint8_t number);


#endif

