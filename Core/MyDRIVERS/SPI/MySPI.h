#ifndef MYSPI_H
#define MYSPI_H
#include "stdint.h"
#include "stm32f446xx.h"
#include "gpiox.h"
#include "stdlib.h"

typedef enum{
	MSB=1,
	LSB
}spi_frame_format;
void SPIx_init(SPI_TypeDef *spi,GPIO_TypeDef *portCS,uint8_t CS,GPIO_TypeDef *portDC,uint8_t DC,GPIO_TypeDef *portRST,uint8_t RST,uint32_t frequency_Mhz,spi_frame_format format);
void SPIx_Tranmsit(SPI_TypeDef *spi,GPIO_TypeDef *port,uint8_t CS,uint8_t data);
void SPIx_pin_LOW(GPIO_TypeDef *port,uint8_t pin);
void SPIx_pin_HIGH(GPIO_TypeDef *port,uint8_t pin);

#endif
