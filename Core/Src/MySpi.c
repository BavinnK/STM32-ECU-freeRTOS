#include "stm32f446xx.h"

void spi_init(void){
	RCC->AHB1ENR|=(1<<2);//ENABLE GPIOC CLOCK

}
