#ifndef TFT_BRIDGE_H
#define TFT_BRIDGE_H

#ifdef __cplusplus
extern "C"{
#endif
#include "spi.h"
void tft_cs_high(void);
void tft_cs_low(void);
void tft_dc_high(void);
void tft_dc_low(void);
void tft_rst_high(void);
void tft_rst_low(void);
void tft_spi_tranmit(uint8_t data);
void delay_us_tft(uint32_t us);

#ifdef __cplusplus
}

#endif
#endif
