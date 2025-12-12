#include "tft_bridge.h"
#include "stm32f446xx.h"
#include "spi.h"

//pins  for clarity
#define CS_PORT GPIOC
#define CS_PIN  0
#define DC_PIN	1
#define RST_PIN	2

void tft_cs_high(void) {
	CS_PORT->BSRR |= (1 << CS_PIN);
}
void tft_cs_low(void) {
	CS_PORT->BSRR |= (1 << (CS_PIN + 16));
}

void tft_dc_high(void) {
	CS_PORT->BSRR |= (1 << DC_PIN);
}
void tft_dc_low(void) {
	CS_PORT->BSRR |= (1 << DC_PIN + 17);
}

void tft_rst_high(void) {
	CS_PORT->BSRR |= (1 << RST_PIN);
}
void tft_rst_low(void) {
	CS_PORT->BSRR |= (1 << RST_PIN + 18);
}
void delay_us_tft(uint32_t us) {
	for (uint32_t i = 0; i < us * 12; i++) {
		__asm__("nop");
	}
}

//this calls our spi func that we created in MySpi files
void tft_spi_transmit(uint8_t data) {
	spi_transmit(&data, 1);
}
