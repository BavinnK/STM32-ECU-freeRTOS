#ifndef HCSR04_H_
#define HCSR04_H_

#include "stm32f446xx.h"
#include <stdint.h>

void hcsr04_init(void);
void hcsr04_trig(void);
uint32_t hcsr04_get_pulse_width(void);
void delay_us(uint32_t us);

#endif
