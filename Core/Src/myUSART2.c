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
    // 1. Enable clocks
    RCC->AHB1ENR |= (1 << 0);   // GPIOA
    RCC->APB1ENR |= (1 << 17);  // USART2

    // 2. Configure PA2 (TX) as Alternate Function
    GPIOA->MODER &= ~(3 << (2*2)); // clear mode bits
    GPIOA->MODER |=  (2 << (2*2)); // AF mode
    GPIOA->OTYPER &= ~(1 << 2);    // push-pull
    GPIOA->OSPEEDR |= (3 << (2*2)); // high speed
    GPIOA->PUPDR &= ~(3 << (2*2));  // no pull-up/down

    // 3. Set AF7 for PA2
    GPIOA->AFR[0] &= ~(0xF << 8);   // clear
    GPIOA->AFR[0] |=  (7 << 8);     // AF7 = USART2

    // 4. Baud rate 9600 @ APB1=45MHz
    USART2->BRR = (292 << 4) | 15;

    // 5. Enable USART, TX only
    USART2->CR1 = (1 << 13) | (1 << 3); // UE | TE
}

