#include "MyDMA.h"
static inline void DMA_config(DMA_TypeDef *dma){
	if(dma==DMA1){
		RCC->AHB1ENR|=(1<<21);
	}
	else if(dma==DMA2){
		RCC->AHB1ENR|=(1<<22);
	}
	else return;
}
static inline void clear_flags(DMA_Stream_TypeDef *stream){
	if(stream==DMA1_Stream0){
		DMA1->LIFCR|=(1<<0)|(0b1111<<2);
	}
	else if(stream==DMA1_Stream1){
		DMA1->LIFCR|=(1<<6)|(0b1111<<8);
	}
	else if(stream==DMA1_Stream2){
		DMA1->LIFCR|=(1<<16)|(0b1111<<18);
	}
	else if(stream==DMA1_Stream3){
		DMA1->LIFCR|=(1<<22)|(0b1111<<24);
	}
	else if(stream==DMA1_Stream4){
		DMA1->HIFCR|=(1<<0)|(0b1111<<2);
	}
	else if(stream==DMA1_Stream5){
		DMA1->HIFCR|=(1<<6)|(0b1111<<8);
	}
	else if(stream==DMA1_Stream6){
		DMA1->HIFCR|=(1<<16)|(0b1111<<18);
	}
	else if(stream==DMA1_Stream7){
		DMA1->HIFCR|=(1<<22)|(0b1111<<24);
	}
	else if(stream==DMA2_Stream0){
		DMA2->LIFCR|=(1<<0)|(0b1111<<2);
	}
	else if(stream==DMA2_Stream1){
		DMA2->LIFCR|=(1<<6)|(0b1111<<8);
	}
	else if(stream==DMA2_Stream2){
		DMA2->LIFCR|=(1<<16)|(0b1111<<18);
	}
	else if(stream==DMA2_Stream3){
		DMA2->LIFCR|=(1<<22)|(0b1111<<24);
	}
	else if(stream==DMA2_Stream4){
		DMA2->HIFCR|=(1<<0)|(0b1111<<2);
	}
	else if(stream==DMA2_Stream5){
		DMA2->HIFCR|=(1<<6)|(0b1111<<8);
	}
	else if(stream==DMA2_Stream6){
		DMA2->HIFCR|=(1<<16)|(0b1111<<18);
	}
	else if(stream==DMA2_Stream7){
		DMA2->HIFCR|=(1<<22)|(0b1111<<24);
	}
}
void DMAx_init(DMA_TypeDef *DMAx,DMA_config_t* DMA_CONFIG){
	DMA_config(DMAx);
	DMA_CONFIG->DMA_STREAM->CR&=~(1);//disable stream first
	//while (DMA_Stream->CR & DMA_SxCR_EN);
	while(DMA_CONFIG->DMA_STREAM->CR&DMA_SxCR_EN);
	clear_flags(DMA_CONFIG->DMA_STREAM);//clear flags
	DMA_CONFIG->DMA_STREAM->CR=0;
	DMA_CONFIG->DMA_STREAM->CR|=(DMA_CONFIG->CHANNEL<<25)|
								(DMA_CONFIG->PRIORITY<<16)|
								(DMA_CONFIG->MEMORY_DATA_SIZE<<13)|
								(DMA_CONFIG->PERIPHERAL_DATA_SIZE<<11)|
								(1<<10)|//Memory address pointer incremented after each data transfer (increment is done according to MSIZE)
								(DMA_CONFIG->MODE<<8)|
								(DMA_CONFIG->DIRECTION<<6);

	DMA_CONFIG->DMA_STREAM->NDTR=DMA_CONFIG->LENGTH;
	DMA_CONFIG->DMA_STREAM->PAR=(uint32_t)DMA_CONFIG->PERIPHERAL_ADDR;//even if the pointer type is uint_32 the compiler complains so  i had to cast it again
	DMA_CONFIG->DMA_STREAM->M0AR=(uint32_t)DMA_CONFIG->MEMORY_ADDR;
	DMA_CONFIG->DMA_STREAM->M1AR=0;//SINCE we don't use double buffer mode we will ignore second address register
	DMA_CONFIG->DMA_STREAM->CR|=1;

}
