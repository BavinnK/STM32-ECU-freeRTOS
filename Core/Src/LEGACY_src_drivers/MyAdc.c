#include <MYadc.h>
#include "stm32f446xx.h"

void adc_init(void) {
	// PA0 for the LM35 ADC1 IN0
	// PA1 for the pot  ADC1 IN1

	RCC->AHB1ENR |= (1 << 0);	// ENABLE GPIOA
	RCC->APB2ENR |= (1 << 8);   // ENABLE ADC1

	// Set PA0 and PA1 to analog mode
	GPIOA->MODER &= ~(0b1111);
	GPIOA->MODER |= (0b11) | (0b11 << 2);	// PA0 and PA1

	// VERY IMPORTANT for LM35: long sample time
	// Channel 0 (PA0)
	ADC1->SMPR2 |= (0b111 << 0);	// 480 cycles for CH0
	// Channel 1 (PA1)
	ADC1->SMPR2 |= (0b111 << 3);	// 480 cycles for CH1

	// Enable ADC
	ADC1->CR2 |= (1 << 0);

	// Small delay to let ADC stabilize
	for (volatile int i = 0; i < 10000; i++);

	// Calibrate ADC (IMPORTANT to remove offset error)
	ADC1->CR2 |= (1 << 3);
	while (ADC1->CR2 & (1 << 3));	// wait until calibration finishes
}

uint16_t adc_read(uint8_t channel) {

	// Clear SQ1 (we use only one conversion)
	ADC1->SQR3 &= ~(0b11111);

	// Select channel:
	// channel 0 -> PA0 (LM35)
	// channel 1 -> PA1 (pot)
	ADC1->SQR3 |= channel;

	// Start conversion by software
	ADC1->CR2 &= ~(1 << 30);	// reset state
	ADC1->CR2 |= (1 << 30);		// start conversion

	// Wait until conversion is complete
	while (!(ADC1->SR & (1 << 1)));

	// Reading DR clears EOC flag automatically
	return ADC1->DR;
}
