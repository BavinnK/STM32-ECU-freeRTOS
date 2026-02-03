#include "MySPI2.h"

static inline void set_format(spi_frame_format format){
	if(format==MSB){
		SPI2->CR1&=~(1<<7);
	}
	else if(format==LSB){
		SPI2->CR1|=(1<<7);
	}
}


static inline uint32_t set_freq(uint32_t freq){
	static const uint16_t psc_table[8]={2,4,8,16,32,64,128,256};
	static const uint32_t pclk=42000000;//prepherial clock of APB1 bus is 42Mhz rightnow, depending on u freq bus u have to change this variable
	uint32_t closest=0,baud_value=0,best_PSC=0,best_closest=0xFFFFFFFF;
	for(int i=0;i<=7;i++){
		baud_value=pclk/psc_table[i];
		closest=abs(baud_value-freq);
		if(closest<=best_closest){
			best_closest=closest;
			best_PSC=i;
		}

	}
	return best_PSC;
}
void SPI2_init(GPIO_TypeDef *portCS,uint8_t CS,GPIO_TypeDef *portDC,uint8_t DC,GPIO_TypeDef *portRST,uint8_t RST,uint32_t frequency_Mhz,spi_frame_format format){

	gpio_set_up config_spi_MOSI,config_spi_MISO,config_spi_SCLK,config_spi_CS,config_spi_DC,config_spi_RST;
	config_spi_MOSI.PINx=1;//PC1
	config_spi_MOSI.MODERx=GPIOx_MODER_AF;
	config_spi_MOSI.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_MOSI.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_MOSI.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_MISO.PINx=2;//PC2
	config_spi_MISO.MODERx=GPIOx_MODER_AF;
	config_spi_MISO.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_MISO.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_MISO.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_SCLK.PINx=10;//PB10
	config_spi_SCLK.MODERx=GPIOx_MODER_AF;
	config_spi_SCLK.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_SCLK.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_SCLK.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_CS.PINx=CS;//user provided CS PIN
	config_spi_CS.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_CS.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_CS.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_CS.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_CS.PINx=DC;//user provided DC PIN
	config_spi_CS.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_CS.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_CS.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_CS.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_CS.PINx=RST;//user provided RST PIN
	config_spi_CS.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_CS.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_CS.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_CS.PUPDRx=GPIOx_PUPDR_NONE;


	gpio_init(GPIOC, &config_spi_MOSI);
	gpio_init(GPIOC, &config_spi_MISO);
	gpio_init(GPIOB, &config_spi_SCLK);
	gpio_init(portCS, &config_spi_CS);
	gpio_init(portDC, &config_spi_DC);
	gpio_init(portRST, &config_spi_RST);

	GPIOC->AFR[0]&=~((0b1111<<4*1)|(0b1111<<4*2));
	GPIOB->AFR[1]&=~(0b1111<<4*(10-8));
	GPIOC->AFR[0]|=((5<<4*1)|(5<<4*2));
	GPIOB->AFR[1]|=(5<<4*(10-8));

	RCC->APB1ENR|=(1<<14);//SPI2 CLK EN
	SPI2->CR1&=~((1<<6)|(0b111<<3)|(1<<1));//DISABLE SPI2 FIRST,and clear baud control bits, and then set the clock polarity to low
	set_format(format);
	SPI2->CR1|=(set_freq(frequency_Mhz)<<3)|(1<<2)|(1<<0);//set the spi to master, then set the freq that was provided by the user
	//then set the clock phase so in the second edge the transmission of data beginst the first edge is just a hand shake with the slave device
	SPI2->CR1|=(3<<8)|(1<<6);//we set both SSM AND SSI to one, basicallly we tell the spi hey i wanna handle the chip select dont worry, then enable the prepherial

}
void SPI2_Transmit(void* data,uint16_t size){
	for(int i=0;i<size;i++){
		while(!(SPI2->SR&(1<<1)));//WAIT UNTIL THE TRANSMIT BUFFER IS EMPTY, afterwards send the data
		SPI2->DR=((uint8_t *)(data))[i];
	}
	while(SPI2->SR&(1<<7));//wait until spi2 is no longer busy
	(void)SPI2->DR;//clear the DR cuz we only send data we dont wanna get any data
}
void SPI2_pin_LOW(GPIO_TypeDef *port,uint16_t pin){
	gpio_reset(port, pin);//low
}
void SPI2_pin_HIGH(GPIO_TypeDef *port,uint16_t pin){
	gpio_set(port, pin);//high
}
