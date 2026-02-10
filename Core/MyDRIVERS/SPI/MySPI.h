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
void SPIx_init(SPI_TypeDef *spi,GPIO_TypeDef *portCS,uint16_t CS,GPIO_TypeDef *portDC,uint16_t DC,GPIO_TypeDef *portRST,uint16_t RST,uint32_t frequency_Mhz,spi_frame_format format);
void SPIx_Transmit(SPI_TypeDef *spi,void* data,uint16_t size);
void SPIx_pin_LOW(GPIO_TypeDef *port,uint16_t pin);
void SPIx_pin_HIGH(GPIO_TypeDef *port,uint16_t pin);

#endif
