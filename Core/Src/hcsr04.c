#include "hcsr04.h"
void hcsr04_init(void) {
	//PA9 for trig and PA8 for echo
	RCC->AHB1ENR |= (0b1);
	RCC->APB2ENR |= (0b1);
	//configuring triger pin PA9 for output
	GPIOA->MODER &= ~((1 << 19) | (1 << 18));
	GPIOA->MODER |= ((1 << 18));
	GPIOA->OTYPER &= ~(1 << 9);    //enable push pull
	GPIOA->PUPDR &= ~((1 << 19) | (1 << 18));    //disable push pull resistor

	//configuring echo pin PA8
	GPIOA->MODER &= ~((1 << 17) | (1 << 16));
	GPIOA->MODER |= ((1 << 17));
	GPIOA->AFR[1] &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
	GPIOA->AFR[1] |= (1 << 0);

	//TIMER 1 conifuration
	//we will set the freq of the timer to 1Mhz so each tick is 1us
	//and we will set CH1 as normal input mode
	TIM1->PSC = 15;
	TIM1->ARR = 0xFFFF;	//we want the timer to count as long as possible for the 16 bit is 65536
	TIM1->CCMR1 &= ~(0b11 << 1);
	TIM1->CCMR1 |= (0b01 << 0);
	TIM1->CCER |= (1 << 3) | (0b11 << 0);

	//now for the INT coniguration
	TIM1->DIER|=(1<<1);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
}
