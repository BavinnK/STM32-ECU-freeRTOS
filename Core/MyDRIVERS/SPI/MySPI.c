#include "MySPI.h"

static inline void set_format(SPI_TypeDef *spi,spi_frame_format format){
	if(format==MSB){
		spi->CR1&=~(1<<7);
	}
	else if(format==LSB){
		spi->CR1|=(1<<7);
	}
}


static inline void SPI_set(SPI_TypeDef *spi,uint32_t frequency_Mhz,spi_frame_format format){
	if(spi==SPI1){
		gpio_set_up config_spi_MOSI,config_spi_SCLK;
		config_spi_MOSI.PINx=7;//PA7
		config_spi_MOSI.MODERx=GPIOx_MODER_AF;
		config_spi_MOSI.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
		config_spi_MOSI.OTYPERx=GPIOx_OTYPER_PP;
		config_spi_MOSI.PUPDRx=GPIOx_PUPDR_NONE;

		config_spi_SCLK.PINx=5;//PA5
		config_spi_SCLK.MODERx=GPIOx_MODER_AF;
		config_spi_SCLK.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
		config_spi_SCLK.OTYPERx=GPIOx_OTYPER_PP;
		config_spi_SCLK.PUPDRx=GPIOx_PUPDR_NONE;

		gpio_init(GPIOA, &config_spi_MOSI);

		gpio_init(GPIOA, &config_spi_SCLK);


		GPIOA->AFR[0]&=~((15<<(7*4))|(15<<(5*4)));
		GPIOA->AFR[0]|=(5<<(7*4))|(5<<(5*4));
		RCC->APB2ENR|=(1<<12);
	}
	else if(spi==SPI2){
		gpio_set_up config_spi_MOSI,config_spi_SCLK;
		config_spi_MOSI.PINx=1;//PC1
		config_spi_MOSI.MODERx=GPIOx_MODER_AF;
		config_spi_MOSI.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
		config_spi_MOSI.OTYPERx=GPIOx_OTYPER_PP;
		config_spi_MOSI.PUPDRx=GPIOx_PUPDR_NONE;


		config_spi_SCLK.PINx=10;//PB10
		config_spi_SCLK.MODERx=GPIOx_MODER_AF;
		config_spi_SCLK.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
		config_spi_SCLK.OTYPERx=GPIOx_OTYPER_PP;
		config_spi_SCLK.PUPDRx=GPIOx_PUPDR_NONE;



		gpio_init(GPIOC, &config_spi_MOSI);

		gpio_init(GPIOB, &config_spi_SCLK);


		GPIOC->AFR[0]&=~((0b1111<<4*1)|(0b1111<<4*2));
		GPIOB->AFR[1]&=~(0b1111<<4*(10-8));
		GPIOC->AFR[0]|=((5<<4*1)|(5<<4*2));
		GPIOB->AFR[1]|=(5<<4*(10-8));

		RCC->APB1ENR|=(1<<14);//SPIx CLK EN
	}
}
void SPIx_init(SPI_TypeDef *spi,GPIO_TypeDef *portCS,uint16_t CS,GPIO_TypeDef *portDC,uint16_t DC,GPIO_TypeDef *portRST,uint16_t RST,uint32_t frequency_Mhz,spi_frame_format format){
	gpio_set_up config_spi_CS,config_spi_DC,config_spi_RST;
	config_spi_CS.PINx=CS;//user provided CS PIN
	config_spi_CS.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_CS.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_CS.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_CS.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_DC.PINx=DC;//user provided DC PIN
	config_spi_DC.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_DC.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_DC.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_DC.PUPDRx=GPIOx_PUPDR_NONE;

	config_spi_RST.PINx=RST;//user provided RST PIN
	config_spi_RST.MODERx=GPIOx_MODER_OUTPUT;
	config_spi_RST.OSPEEDRx=GPIOx_OSPEEDR_HIGH_SP;
	config_spi_RST.OTYPERx=GPIOx_OTYPER_PP;
	config_spi_RST.PUPDRx=GPIOx_PUPDR_NONE;

	gpio_init(portCS, &config_spi_CS);
	gpio_init(portDC, &config_spi_DC);
	gpio_init(portRST, &config_spi_RST);
	SPI_set(spi, frequency_Mhz, format);
	spi->CR1&=~((1<<6)|(0b111<<3)|(1<<1));//DISABLE SPIx FIRST,and clear baud control bits, and then set the clock polarity to low
	set_format(spi,format);
	spi->CR1&=~(1<<10);
	spi->CR1&=~(0b111<<3);
	spi->CR1|=(0b110<<3)|(1<<2);//set the spi to master, then set the freq that was provided by the user
	//then set the clock phase so in the second edge the transmission of data beginst the first edge is just a hand shake with the slave device
	spi->CR1|=(3<<8)|(1<<6);//we set both SSM AND SSI to one, basicallly we tell the spi hey i wanna handle the chip select dont worry, then enable the prepherial
	spi->CR1&=~(1<<11);//clear DFF bit to set it to 8 bit format
	spi->CR1|=(1<<2);//set master config
}
void SPIx_Transmit(SPI_TypeDef *spi, void *data, uint16_t size) {
    uint8_t *p = data;

    for (uint16_t i = 0; i < size; i++) {
        while (!(spi->SR & SPI_SR_TXE));
        spi->DR = p[i];

        while (!(spi->SR & SPI_SR_RXNE));
        (void)spi->DR;
    }

    while (spi->SR & SPI_SR_BSY); // THIS is the missing piece
}

void SPIx_pin_LOW(GPIO_TypeDef *port,uint16_t pin){
	gpio_reset(port, pin);//low
}
void SPIx_pin_HIGH(GPIO_TypeDef *port,uint16_t pin){
	gpio_set(port, pin);//high
}
