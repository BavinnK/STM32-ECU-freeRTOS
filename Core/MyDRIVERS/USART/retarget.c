#include "unistd.h"
#include "MyUsart.h"

int _write(int file,char *ptr,int len){
	(void)file;//just ignore

	for(int i=0;i<len;i++){
		Usart2_SendByte(ptr[i]);
	}
	return len;
}
