#include "relay.h"

void relay_init(void){
	RCC->AHB1ENR|=(1<<1);//ENABLE GPIOB clock
	//the plan is to set the LOW RELAY to PB10, MID RELAY to PB5, HIGH RELAY to PB4
	GPIOB->MODER&=~((1<<21)|(1<<20)|(1<<11)|(1<<10)|(1<<9)|(1<<8));
	GPIOB->MODER|=(1<<20)|(1<<8)|(1<<6);
}
void relay_set_fan_speed(FanSpeed_t speed){
	switch(speed){

	case FAN_OFF://all is LOW
		GPIOB->BSRR|=(1<<26)|(1<<21)|(1<<20);
	case FAN_LOW://PB10 HIGH ,PB5 LOW ,PB4 LOW
		GPIOB->BSRR|=(1<<10);
		GPIOB->BSRR|=(1<<21)|(1<<20);
	case FAN_MEDIUM://BP5 HIGH, PB10 LOW, PB4 LOW
		GPIOB->BSRR|=(1<<5);
		GPIOB->BSRR|=(1<<26)|(1<<20);
	case FAN_HIGH:
		GPIOB->BSRR|=(1<<4);
		GPIOB->BSRR|=(1<<26)|(1<<21);

	}
}

