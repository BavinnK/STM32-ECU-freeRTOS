#include "stm32f446xx.h"
#include <stdint.h>

void systemClock_180MHz(void){
	RCC->CR|=(1<<16);				//enable external 8Mhz oscillator HSE
	while(!(RCC->CR&(1<<17)));		//wait for the HSE clock to be ready
	RCC->APB1ENR|=(1<<28);			//since we are gonna run the chip at 180Mhz, it needs more juice i mean voltage
	PWR->CR|=(3<<14);				//we set the scale mode to 1 max performance
	PWR->CR|=(1<<16);				//we need a special sequence cuz the overdrive itself is not enough for the ower we enable overdrive
	while(!(PWR->CSR&(1<<16)));		//wait until overdrive is enabled
	PWR->CR|=(1<<17);				//after overdrive is enabled then we have to enable the switch overdrive
	while((PWR->CSR&(1<<17)));		//wait until overdrive switching is enabled
	RCC->CFGR&=~(0b111111<<10);	//now we clear APB1 AND APB2 bits why cuz those two bus cant run at 180 Mhz
	RCC->CFGR|=(4<<13);				//APB2 is high speed bus runs at 90 Mhz we divide the fclk by 2 which is 180/2=90
	RCC->CFGR|=(5<<10);				//APB1 is low speed bus runs at 45Mhz so we have to divide the fclk by 4 to get 45 which is 180/4=45
	/*
	 * the CPU will now run at 180Mhz, but we have a problem
	 * which is the internal perpherials like the flash
	 * cannot keep up with the speed of the CPU so before we switch to PLL mode we have to
	 * configure flash wait states and caches
	 * 0 WS → 0–30 MHz
	 * 1 WS → 30–60 MHz
	 * 2 WS → 60–90 MHz
	 * …
	 * 5 WS → 168–180 MHz
	 * WS == wait state
	 * this is optional but its better to enable flash prefetch
	 * then we have to enable ID/IC cache bits normally in under 90 Mhz cache is off but for hight speeds
	 * we have to turn them on
	 */
	FLASH->ACR&=~(0b1111);			//clear the flash latency
	FLASH->ACR|=(5<<0)|(7<<8);		//then we set it to 5 wait state, and enable prefetch, then enable data cache and Instruction cache
	RCC->PLLCFGR&=~(0b111111);		//clear PLLM bits
	RCC->PLLCFGR|=(8);				//divide the HSE clock by 8, the target clock after division should be between 1 to 2 Mhz
	RCC->PLLCFGR&=~(0b111111111);	//clear PLLN bits
	RCC->PLLCFGR|=(360<<6);			//then multiply the 1 Mhz that we divided in the PLLM to 360, the multiply spot should be between 192Mhz to 432Mhz i want 360 to get 180 easily
	RCC->PLLCFGR&=~(3<<16);			//set the PLLP bits to 00 which means the PLLN freq will be divided by 2, the 360 that we got we divide by 2 and kaboom we got 180Mhz
	RCC->PLLCFGR|=(1<<22);			//we have to tell the PLL to look at HSE cuz in default it looks at HSI
	RCC->CR|=(1<<24);				//enable PLL
	while(!(RCC->CR&(1<<25)));		//wait for the PLL to stabilize and locked
	RCC->CFGR&=~(2);				//clear the SW bits
	RCC->CFGR|=2;					//switch to PLL from HSI
	while(!(RCC->CFGR&(1<<3)));		//wait until the switching is done
}
