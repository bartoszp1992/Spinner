#include "main.h"
#include "adc.h"
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

void adcInit(void) {

	HAL_ADC_Start(&hadc);
	adcValue = 2500;
}

void adcRead(void) {

	adcReading = HAL_ADC_GetValue(&hadc);

	if(adcReading > adcValue){
		adcValue++;
	}else{
		adcValue--;
	}

	voltage = ((330 * adcValue) / 4095) * 2;
	batteryState = (60 * (voltage - 340)) / 80;

	if(batteryState >60) batteryState = 59;
	if(batteryState <0) batteryState = 0;

}
