#ifndef MYUSART_H
#define MYUSART_H
#include "stm32f446xx.h"
#include <stdint.h>
#include "gpiox.h"
#include "RingBuffer.h"
void Usart2_SendByte(char ch);
void Usart2_SendString(char *ptr);
void Usart2_init(uint32_t baudRate);
#endif
