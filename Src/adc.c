#include "main.h"
#include "adc.h"
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

void adcInit(void) {
//	if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK) {
//		Error_Handler();
//	}

	if (HAL_ADC_Start_DMA(&hadc, adcReading, 2) != HAL_OK) {
		Error_Handler();
	}

}

void adcConvert(void){
	voltage = ((330*adcReading[0])/4095)*2;
	batteryState = (60*(voltage-340))/80;
}
