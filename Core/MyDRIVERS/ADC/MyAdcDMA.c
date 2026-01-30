#include <MyAdcDMA.h>

static inline GPIO_TypeDef* channel_setup(uint8_t port){//inline helper func for the GPIO port
	if(port>=0 && port<=7){
		return GPIOA;
	}
	else if(port>=8&&port<=9){
		return GPIOB;
	}
	else if(port>=10&&port<=15){
		return GPIOC;
	}
	else{
		while(1);//error
	}
}
static inline void adc_setup(ADC_TypeDef *ptr){
	if(ptr==ADC1){
		RCC->APB2ENR|=(1<<8);//enable adc1
	}
	else if(ptr==ADC2){
		RCC->APB2ENR|=(1<<9);//enable adc2
	}
	else if(ptr==ADC3){
		RCC->APB2ENR|=(1<<10);//enable adc3
	}
	else{
		while(1);//error
	}
}
static inline void channel_adc(ADC_TypeDef *adc_port,uint8_t chn,uint8_t sample){
	if(chn>=0&&chn<=9){
		adc_port->SMPR2&=~((0b111<<(chn*3)));
		adc_port->SMPR2|=(sample<<(chn*3));

	}
	else if(chn>=10&&chn<=15){
		adc_port->SMPR1&=~((0b111<<(chn*3)));
		adc_port->SMPR1|=(sample<<(chn*3));
	}
}
void adc_dma_init(ADC_TypeDef *adc_port,adc_config_t *ptr,DMA_TypeDef *DMAx,DMA_config_t* DMAx_config,uint8_t num_of_channels) {
	for(int i=0;i<num_of_channels;i++){
		gpio_set_up config;
		config.MODERx=GPIOx_MODER_ANALOG;
		config.OSPEEDRx=GPIOx_OSPEEDR_LOW_SP;//dont care for adc
		config.OTYPERx=GPIOx_OTYPER_PP;//dont care for adc
		config.PINx=ptr->channel[i];
		config.PUPDRx=GPIOx_PUPDR_NONE;
		GPIO_TypeDef *port=channel_setup(ptr->channel[i]);
		gpio_init(port, &config);
		channel_adc(adc_port, ptr->channel[i], ptr->sample_time);
	}
	adc_setup(adc_port);
	//enable ADCx
	adc_port->CR1|=(1<<8);//enable scan mode
	adc_port->CR2 |= (1 << 0)|(1<<1);
	adc_port->CR2&=~(1<<30);//disable conversion

	//small delay to let ADC stabilize
	for (volatile uint16_t i = 0; i < 1000; i++);
	adc_port->SQR1=0;
	adc_port->SQR2=0;
	adc_port->SQR3=0;
	adc_port->CR2 |= (3<<8);
	for(uint8_t i=0;i<num_of_channels;i++){//the users passes which channel they want to use and by this loop we will set it up
		if(i<6){
			adc_port->SQR3|=(ptr->channel[i]<<(i*5));
		}
		else if(i<12){
			adc_port->SQR2|=(ptr->channel[i]<<((i*5)-35));
		}
		else if(i<16){
			adc_port->SQR1|=(ptr->channel[i]<<((i*5)-65));
		}
		else while(1);
	}
	adc_port->SQR1&=~(0b1111<<20);
	adc_port->SQR1|=(num_of_channels-1)<<20;//why -1 cuz 0 is count as 1 conversion

	DMAx_init(DMAx, DMAx_config);
	adc_port->CR2|=(1<<30);
}


