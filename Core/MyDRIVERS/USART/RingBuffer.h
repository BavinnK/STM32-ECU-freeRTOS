#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"

#define RING_BUF_SIZE 256 //size of our buffer, which is 256 byte

typedef struct {
    volatile uint8_t buffer[RING_BUF_SIZE];
    volatile uint32_t head;
    volatile uint32_t tail;
} RingBuffer_t;

void RingBuffer_Init(RingBuffer_t *rb);
bool RingBuffer_IsEmpty(RingBuffer_t *rb);
bool RingBuffer_IsFull(RingBuffer_t *rb);
bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data);
bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data);

#endif
