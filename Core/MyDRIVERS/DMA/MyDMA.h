#ifndef MYDMA_H
#define MYDMA_H
#include "stm32f446xx.h"
#include <stdint.h>

typedef enum{
	PRIOTITY_LOW=0,
	PRIOTITY_MED,
	PRIOTITY_HIGH,
	PRIOTITY_VERY_HIGH
}dma_priority;
typedef enum{
	MEM_BYTE=0,
	MEM_HALF_WORD,
	MEM_WORD
}mem_size;
typedef enum{
	PER_BYTE=0,
	PER_HALF_WORD,
	PER_WORD
}per_size;
typedef enum{
	PER_TO_MEM=0,
	MEM_TO_PER,
	MEM_TO_MEM
}dma_direction;
typedef enum{
	NORMAL=0,
	CIRCULAR
}dma_mode;
typedef struct{
	DMA_Stream_TypeDef * DMA_STREAM;
	uint8_t CHANNEL;
	uint32_t *PERIPHERAL_ADDR;
	uint32_t *MEMORY_ADDR;
	uint32_t LENGTH;
	dma_priority PRIORITY;
	mem_size MEMORY_DATA_SIZE;
	per_size PERIPHERAL_DATA_SIZE;
	dma_direction DIRECTION;
	dma_mode MODE;
}DMA_config_t;

void DMAx_init(DMA_TypeDef *DMAx,DMA_config_t* DMA_CONFIG);

#endif
