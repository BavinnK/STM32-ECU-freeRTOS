#include <MyHcsr04.h>
#include "FreeRTOS.h"
#include "semphr.h"
extern SemaphoreHandle_t xHcsr04Semaphore;

#define TOP_VAL 0xFFFF
volatile uint32_t start_time = 0, end_time = 0, difference = 0;
volatile uint8_t is_first_cap = 0;

void hcsr04_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	/* ---------- PA10 : TRIG (OUTPUT) ---------- */
	GPIOA->MODER &= ~(3 << (10 * 2));
	GPIOA->MODER |= (1 << (10 * 2));     // Output
	GPIOA->OTYPER &= ~(1 << 10);          // Push-pull
	GPIOA->PUPDR &= ~(3 << (10 * 2));     // No pull

	/* ---------- PA8 : ECHO (AF TIM1_CH1) ---------- */
	GPIOA->MODER &= ~(3 << (8 * 2));
	GPIOA->MODER |= (2 << (8 * 2));     // Alternate function

	GPIOA->AFR[1] &= ~(0xF << 0);
	GPIOA->AFR[1] |= (0x1 << 0);         // AF1 = TIM1

	GPIOA->PUPDR &= ~(3 << (8 * 2));      // No pull

	/* ---------- TIM1 CONFIG ---------- */
	TIM1->CR1 = 0;
	TIM1->PSC = 179;       // 84 MHz / (83+1) = 1 MHz → 1 µs tick
	TIM1->ARR = TOP_VAL;

	/* Input capture on CH1 */
	TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0;     // CC1 mapped to TI1

	/* Capture rising edge initially */
	TIM1->CCER = 0;
	TIM1->CCER |= TIM_CCER_CC1E;

	/* Enable CC interrupt */
	TIM1->DIER |= TIM_DIER_CC1IE;

	/* Force update (VERY IMPORTANT) */
	TIM1->EGR |= TIM_EGR_UG;

	/* Enable timer */
	TIM1->CR1 |= TIM_CR1_CEN;

	/* NVIC */

}

void TIM1_CC_IRQHandler(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (TIM1->SR & TIM_SR_CC1IF) {
		if (is_first_cap == 0) {
			start_time = TIM1->CCR1;
			is_first_cap = 1;

			/* Switch to falling edge */
			TIM1->CCER |= TIM_CCER_CC1P;
		} else {
			end_time = TIM1->CCR1;

			if (end_time >= start_time)
				difference = end_time - start_time;
			else
				difference = (TOP_VAL - start_time) + end_time;

			is_first_cap = 0;

			/* Back to rising edge */
			TIM1->CCER &= ~TIM_CCER_CC1P;
			xSemaphoreGiveFromISR(xHcsr04Semaphore, &xHigherPriorityTaskWoken);
		}
		TIM1->SR &= ~(1 << 1);     //clear manually

	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);  //we will yeild the semophore
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
uint32_t hcsr04_get_pulse_width(void) {
	return difference;
}
