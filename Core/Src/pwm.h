#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32f446xx.h"
#include <stdint.h>

void pwm_fan_init(uint16_t freq_hz,uint8_t duty);
void pwm_fan_duty_set(uint8_t duty);

#endif
