#ifndef MYSPI2_H
#define MYSPI2_H
#include "stdint.h"
#include "stm32f446xx.h"
#include "gpiox.h"
#include "stdlib.h"

typedef enum{
	MSB=1,
	LSB
}spi_frame_format;
void SPI2_init(GPIO_TypeDef *portCS,uint8_t CS,GPIO_TypeDef *portDC,uint8_t DC,GPIO_TypeDef *portRST,uint8_t RST,uint32_t frequency_Mhz,spi_frame_format format);
void SPI2_Transmit(void* data,uint16_t size);
void SPI2_pin_LOW(GPIO_TypeDef *port,uint16_t pin);
void SPI2_pin_HIGH(GPIO_TypeDef *port,uint16_t pin);

#endif
