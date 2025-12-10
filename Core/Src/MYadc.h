#ifndef MYADC_H
#define MYADC_H

#include "stdint.h"
#include "stm32f446xx.h"

void adc_init(void);
uint16_t adc_read(uint8_t channel);


#endif



