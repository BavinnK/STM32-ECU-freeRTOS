#ifndef MYUSART2_H
#define MYUSART2_H

#include "stdint.h"
#include "stm32f446xx.h"

void send_char(char ch);
void send_str(char *ptr);
void USART2_init(void);

#endif
