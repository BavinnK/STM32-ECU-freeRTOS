#include "RingBuffer.h"

bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data){
	if(RingBuffer_IsFull(rb)) return false;
	rb->buffer[rb->head]=data;
	rb->head = (rb->head + 1) & (RING_BUF_SIZE - 1);// wee need the bitwise and to wrap around
	return true;//means data was written to the buffer

}
bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data){
	if(RingBuffer_IsEmpty(rb)) return false;
	*data=rb->buffer[rb->tail];//we give the tail data to the pointer to read
	rb->tail = (rb->tail + 1) & (RING_BUF_SIZE - 1);//move the tail one front
	return true;
}




bool RingBuffer_IsEmpty(RingBuffer_t *rb){
	if(rb->head==rb->tail) return true;
	else 				   return false;

}
bool RingBuffer_IsFull(RingBuffer_t *rb){
	if(((rb->head+1)&(RING_BUF_SIZE-1))==rb->tail) return true;
	else   					 return false;
}
