#include <MyUsart2.h>

void send_char(char ch) {
	while (!(USART2->SR & (1 << 7)))
		;
	USART2->DR = ch;
}
void send_str(char *ptr) {
	while (*ptr) {
		send_char(*ptr);
		ptr++;
	}
}

void USART2_init(void) {
	//PA2 TX, PA3 RX
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 17);
	GPIOA->MODER &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
	GPIOA->MODER |= ((1 << 7) | (0 << 6) | (1 << 5) | (0 << 4));//BOTH PA2 AND PA3 TO alternative mode
	GPIOA->AFR[0] &= ~((1 << 11) | (1 << 10) | (1 << 9) | (1 << 8));//CLEARING FOR PA2
	GPIOA->AFR[0] &= ~((1 << 15) | (1 << 14) | (1 << 13) | (1 << 12));//CLEARING FOR PA3
	GPIOA->AFR[0] |= (1 << 14) | (1 << 13) | (1 << 12);	//SETTING THE AFR REG FOR PA3
	GPIOA->AFR[0] |= ((1 << 10) | (1 << 9) | (1 << 8)); //SETTING THE AFR REG FOR PA2
	USART2->BRR = (104 << 4) | (3);
	USART2->CR1 |= (1 << 13) | (1 << 3);
}
