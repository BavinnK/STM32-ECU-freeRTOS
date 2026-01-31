#ifndef GPIOX_H_
#define GPIOX_H_

#include "stdint.h"
#include "stm32f446xx.h"

typedef enum {
	GPIOx_MODER_INPUT = 0b00,
	GPIOx_MODER_OUTPUT = 0b01,
	GPIOx_MODER_AF = 0b10,
	GPIOx_MODER_ANALOG = 0b11
} gpio_mode_t;

typedef enum {
	GPIOx_OTYPER_PP = 0b00,
	GPIOx_OTYPER_OD = 0b01
} gpio_otype_t;

typedef enum {
	GPIOx_OSPEEDR_LOW_SP = 0b00,
	GPIOx_OSPEEDR_MED_SP = 0b01,
	GPIOx_OSPEEDR_FAST_SP = 0b10,
	GPIOx_OSPEEDR_HIGH_SP = 0b11
} gpio_speed_t;
typedef enum {
	GPIOx_PUPDR_NONE = 	0b00,
	GPIOx_PUPDR_UP = 	0b01,
	GPIOx_PUPDR_DOWN = 	0b10
} gpio_pull_t;
typedef struct {
	uint8_t PINx;
	gpio_mode_t MODERx;
	gpio_otype_t OTYPERx;
	gpio_speed_t OSPEEDRx;
	gpio_pull_t PUPDRx;
} gpio_set_up;

void gpio_init(GPIO_TypeDef *port, gpio_set_up *ptr);

void gpio_set(GPIO_TypeDef *port,uint8_t pin);
void gpio_reset(GPIO_TypeDef *port,uint8_t pin);
#endif
