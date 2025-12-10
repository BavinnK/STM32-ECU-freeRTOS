#include "MYadc.h"
#include "stm32f446xx.h"

void adc_init(void) {
	//PA0 for the LM35 ADC1 IN0
	//PA1 for the pot  ADC1 IN1
	RCC->AHB1ENR |= (1 << 0);	//ENABLE GPIOA
	RCC->APB2ENR |= (1 << 8);   //ENABLE ADC1
	GPIOA->MODER &= ~(0b1111);
	GPIOA->MODER |= (0b11);		//PA0
	GPIOA->MODER |= (0b11 << 2);	//PA1

	ADC1->CR2 &= ~(0b1);
	ADC1->CR2 |= (0b1);

}

uint16_t adc_read(uint8_t channel) {
	ADC1->SQR3 &= ~((0b1111111111));//clearing SQ1 AND SQ2,  SQ1 is gived for PA0 ,and SQ2 for PA1
	ADC1->SQR3 |= (1 << 5) | (0 << 0); //channel 0 == SQ1 and channel 1== SQ2

	if (channel == 0) {
		ADC1->CR2 &= ~(1 << 30);	//reset state then set
		ADC1->CR2 |= (1 << 30);

		while (!(ADC1->SR & (1 << 1)));//we wait until the coversion is complete then return the value

		return ADC1->DR;

	} else if (channel == 1) {
		ADC1->CR2 &= ~(1 << 30);	//reset state then set
		ADC1->CR2 |= (1 << 30);

		while (!(ADC1->SR & (1 << 1)));//we wait until the coversion is complete then return the value

		return ADC1->DR;
	}

	return 0;//if the channel number was wrong the user has to choose 1 or 0 to read

}
