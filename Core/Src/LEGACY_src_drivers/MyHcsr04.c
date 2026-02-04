#include <MyHcsr04.h>
#include "FreeRTOS.h"
#include "semphr.h"
extern SemaphoreHandle_t xHcsr04Semaphore;

#define TOP_VAL 0xFFFF
volatile uint32_t start_time = 0, end_time = 0, diffrence = 0;
volatile uint8_t is_first_cap = 0;

void hcsr04_init(void) {
	//PA10 for trig and PA8 for echo
	RCC->AHB1ENR |= (0b1);
	RCC->APB2ENR |= (0b1);
	//configuring triger pin PA10 for output
	GPIOA->MODER &= ~(( 0b11 << 2*10 ));
	GPIOA->MODER |= ((1 << 20));
	GPIOA->OTYPER &= ~(1 << 10);    //reset state
	GPIOA->PUPDR &= ~(0b11<<2*10);    //disable push pull resistor

	//configuring echo pin PA8
	GPIOA->MODER &= ~((1 << 17) | (1 << 16));
	GPIOA->MODER |= ((1 << 17));
	GPIOA->AFR[1] &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
	GPIOA->AFR[1] |= (1 << 0);

	//TIMER 1 conifuration
	//we will set the freq of the timer to 1Mhz so each tick is 1us
	//and we will set CH1 as normal input mode
	TIM1->PSC = 89;
	TIM1->ARR = 0xFFFF;	//we want the timer to count as long as possible for the 16 bit is 65536
	TIM1->CCMR1 &= ~(0b11);
	TIM1->CCMR1 |= (0b01 << 0);
	TIM1->CCER |= (1 << 3) | (1 << 1) | (1 << 0);
	TIM1->CR1 |= (1 << 0);

	//now for the INT coniguration
	TIM1->DIER |= (1 << 1);
	//NVIC_EnableIRQ(TIM1_CC_IRQn);
}

void TIM1_CC_IRQHandler(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (TIM1->SR & (1 << 1)) {
		if (is_first_cap == 0) {
			//when is_first_cap is 0 it means its rising edge
			start_time = TIM1->CCR1;
			is_first_cap = 1;
		} else {
			end_time = TIM1->CCR1;

			if (start_time < end_time) {
				diffrence = end_time - start_time;
			} else if (start_time > end_time) {
				//when this condition is true means that the ARR got overflowed and reseted to zero
				//got this from AI but its genius, we do this
				//first we make the starttime as smaller than the endtime so we dont get a minus value and thats it and we do our calculation
				diffrence = (TOP_VAL - start_time) + end_time;


			}

			is_first_cap = 0;
			xSemaphoreGiveFromISR(xHcsr04Semaphore, &xHigherPriorityTaskWoken);
		}

		TIM1->SR &= ~(1 << 1);//clear manually

	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//we will yeild the semophore
}
//the interrupt is done
//quick and dirty delay in us
void delay_us_hc(uint32_t us) {
	for (uint32_t i = 0; i < us * 12; i++) {
		__asm__("nop");
	}
}
void hcsr04_trig_hc(void) {
	GPIOA->BSRR = (1 << 10);			//HIGH
	delay_us_hc(10);						//small delay
	GPIOA->BSRR = (1 << 26);		//LOW
}
uint32_t  hcsr04_get_pulse_width(void){
	return diffrence;
}
