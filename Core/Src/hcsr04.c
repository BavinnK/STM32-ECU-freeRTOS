#include "hcsr04.h"
void hcsr04_init(void){
	//PA9 for trig and PA8 for echo
	RCC->AHB1ENR|=(0b1);
	RCC->APB2ENR|=(0b1);
	//configuring triger pin PA9 for output
	GPIOA->MODER&=~((1<<19)|(1<<18));
	GPIOA->MODER|=((1<<18));
	GPIOA->OTYPER&=~(1<<9);    //enable push pull
	GPIOA->PUPDR&=~((1<<19)|(1<<18));//disable push pull resistor

	//configuring echo pin PA8
	GPIOA->MODER&=~((1<<17)|(1<<16));
	GPIOA->MODER|=((1<<17));
	GPIOA->AFR[1]&=~((1<<3)|(1<<2)|(1<<1)|(1<<0));
	GPIOA->AFR[1]|=(1<<0);
}
