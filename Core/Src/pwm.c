#include "pwm.h"
void pwm_fan_init(uint16_t freq_hz,uint8_t duty) {
	const uint32_t fclk_tim = 16000000;
	//we use timer 3 and PA6 for the output
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 1);
	GPIOA->MODER &= ~(0b11 << 12); // Clear the bits for PA6
	GPIOA->MODER |= (0b10 << 12); // Set to Alternate Function (10)
	GPIOA->AFR[0] &= ~(0b1111 << 24); // Clear the bits for PA6
	GPIOA->AFR[0] |= (2 << 24);      // Set AF2
	TIM3->PSC = 15;
	TIM3->ARR = ((fclk_tim) / ((15 + 1) * freq_hz)) - 1;
	pwm_fan_duty_set(duty);
	TIM3->CCMR1 &= ~((1 << 6) | (1 << 5) | (1 << 4) | (1 << 3));
	TIM3->CCMR1 |= ((1 << 6) | (1 << 5) | (1 << 3));
	TIM3->CCER |= (1 << 0);
	TIM3->EGR |= (1 << 0);
	TIM3->CR1 |= (1 << 0);
}
void pwm_fan_duty_set(uint8_t duty) {
	if (duty > 0 && duty <= 100) {
		uint32_t result = (duty * (TIM3->ARR + 1)) / 100;
		TIM3->CCR1 = result;

	}

}
