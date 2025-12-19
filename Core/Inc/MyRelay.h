#ifndef RELAY_H
#define RELAY_H

#include "stm32f446xx.h"
#include <stdint.h>

typedef enum {
    FAN_SPEED_OFF,
    FAN_SPEED_LOW,
    FAN_SPEED_MEDIUM,
    FAN_SPEED_HIGH
} FanSpeed_t;
void relay_init(void);
void relay_set_fan_speed(FanSpeed_t speed);


#endif
