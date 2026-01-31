#include "MyUsart.h"
RingBuffer_t usart2_ring_RX,usart2_ring_TX;
static inline uint32_t set_baud(uint32_t baud){
	/*
	 * the reason i did not put any equation to get the BRR parts which are
	 * mantissa and fraction was so i dont waste cpu cycle and use floating points
	 * which abit hard on teh CPU i was like i will calculate it myself and give it to BRR register
	 * the equation is
	 * USARTDIV=(fclk/(16*baud))
	 * the fclk is the frequency of ABP1 BUS which in my case it's 42 Mhz
	 */
	if(baud==9600) 			return 0x1117;
	else if(baud==14400) 	return 0x0B60;
	else if(baud==19200) 	return 0x08B9;
	else if(baud==38400) 	return 0x045D;
	else if(baud==57600) 	return 0x02D9;
	else if(baud==115200) 	return 0x016D;
	else if(baud==230400) 	return 0x00B6;
	else if(baud==460800) 	return 0x005B;
	else if(baud==921600) 	return 0x002D;
	else 					return 0;
}
void Usart2_init(uint32_t baudRate){
	gpio_set_up config_RX,config_TX;
	config_RX.PINx=3;
	config_RX.MODERx=GPIOx_MODER_AF;
	config_RX.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_RX.OTYPERx=GPIOx_OTYPER_PP;
	config_RX.PUPDRx=GPIOx_PUPDR_UP;

	config_TX.PINx=2;
	config_TX.MODERx=GPIOx_MODER_AF;
	config_TX.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_TX.OTYPERx=GPIOx_OTYPER_PP;
	config_TX.PUPDRx=GPIOx_PUPDR_NONE;

	gpio_init(GPIOA, &config_TX);
	gpio_init(GPIOA, &config_RX);
	RCC->APB1ENR|=(1<<17);
	GPIOA->AFR[0]&=~((0b1111<<(2*4))|(0b1111<<(3*4)));
	GPIOA->AFR[0]|=(7<<2*4)|(7<<3*4);

	USART2->CR1|=(1<<2)|(1<<3)|(1<<13)|(1<<5);
	USART2->BRR=set_baud(baudRate);
	NVIC_EnableIRQ(USART2_IRQn);//enable the USART INT into the NVIC handler
}
void Usart2_SendByte(char ch){
	bool isFull=RingBuffer_Write(&usart2_ring_TX, ch);
	if(isFull){
		USART2->CR1|=(1<<7);

	}

}
void Usart2_SendString(char *ptr){
	while(*ptr){
		Usart2_SendByte(*ptr++);
	}

}
void USART2_IRQHandler(void){
	if(USART2->SR&(1<<5)){
		//if this condition is true means RXNE flag is set
		//and when this flag i set means a data arrived and we have to read that data from the data register and send it to the ring buffer
		uint8_t data=USART2->DR;
		RingBuffer_Write(&usart2_ring_RX, data);
	}
	if(USART2->SR&(1<<7)){
		//when the TXIE flag is set means there is data in the register
		uint8_t data1;
		if(RingBuffer_Read(&usart2_ring_TX, &data1)){
			USART2->DR=data1;
		}
		else USART2->CR1&=~(1<<7);//if the buffer is empty disable the TXE bit
	}
}
