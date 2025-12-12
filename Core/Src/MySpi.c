#include "stm32f446xx.h"

void spi_init(void){
	RCC->APB2ENR|=(1<<12);//ENANBLE SPI1 CLOCK, WE ARE USING SPI1 BC IT'S ON FASTER BUS WHICH IS ABP2 IS FASTER THAN APB1 WHICH SPI2 AND 3 ARE IN THOSE BUSES
	//configure control pins CS=PC0, DC=PC1, RST=PC2 as GPIO Outputs
	RCC->AHB1ENR|=(1<<2)|(1<<0);//ENABLE GPIOC AND GPIOA CLOCK

	GPIOC->MODER&=~((0b11<<4)|(0b11<<2)|(0b11<<0));
	GPIOC->MODER|=((1<<4)|(1<<2)|(1<<0));//output mode
	GPIOC->OSPEEDR|=((0b11<<4)|(0b11<<2)|(0b11<<0));//optional: we configure PC0,PC1,PC2 to high speed output pins

	//configure SPI pins which PA6-> MISO, PA5->SCK, PA7->MOSI
	GPIOA->MODER&=~((1<<15)|(1<<14)|(1<<13)|(1<<12)|(1<<11)|(1<<10));
	GPIOA->MODER|=((1<<15)|(1<<13)|(1<<11));

	GPIOA->AFR[0]&=~((0xF<<28)|(0xF<<24)|(0xF<<20));
	GPIOA->AFR[0]|=(0b0101<<28)|(0b0101<<24)|(0b0101<<20);

	GPIOA->OSPEEDR|=(3<<14)|(3<<12)|(3<<10);

	//CONFIGURE SPI1 prepherials
	SPI1->CR1=0;
	SPI1->CR1|=(1<<9)|(1<<8)|(2<<3)|(1<<2);//baud rate is 2Mhz and master bit is selected,we have to set SSI AND SSM to tell the hardware you are the master
	//dont care about the chip select pin im gonna handle it with my software
	SPI1->CR1|=(1<<6);//finally we enable the spi


}
void spi_transmit(uint8_t *data_ptr,uint32_t size){
	for(uint32_t i=0;i<size;i++){
		while(!(SPI1->SR&(1<<1)));//WAIT UNTIL THE TRANSMIT BUFFER IS EMPTY, afterwards send the data

		SPI1->DR=data_ptr[i];

	}
	//when dont sending after we wait again until the busy flag is cleared
	while(SPI1->SR&(1<<7));
}
