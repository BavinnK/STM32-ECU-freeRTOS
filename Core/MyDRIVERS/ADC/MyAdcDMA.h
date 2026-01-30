#ifndef MYADCDMA_H
#define MYADCDMA_H

#include "stdint.h"
#include "stm32f446xx.h"
#include "gpiox.h"
#include "dma/MyDMA.h"
typedef enum{
	ADCx_CHANNEL_0=0,
	ADCx_CHANNEL_1=1,
	ADCx_CHANNEL_2=2,
	ADCx_CHANNEL_3=3,
	ADCx_CHANNEL_4=4,
	ADCx_CHANNEL_5=5,
	ADCx_CHANNEL_6=6,
	ADCx_CHANNEL_7=7,
	ADCx_CHANNEL_8=8,
	ADCx_CHANNEL_9=9,
	ADCx_CHANNEL_10=10,
	ADCx_CHANNEL_11=11,
	ADCx_CHANNEL_12=12,
	ADCx_CHANNEL_13=13,
	ADCx_CHANNEL_14=14,
	ADCx_CHANNEL_15=15
}adc_channels_t;
typedef struct{
	adc_channels_t channel[16];
	uint8_t sample_time;
}adc_config_t;
void adc_dma_init(ADC_TypeDef *adc_port,adc_config_t *ptr,DMA_TypeDef *DMAx,DMA_config_t* DMAx_config,uint8_t num_of_channels);



#endif


