/*
 *  Théo Folin
 *  2016
 * 	sd_spi.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef SD_SPI_H
#define SD_SPI_H

#include "stm32f4xx_hal.h"
#include "error.h"

#define WAIT_N_MS(n) {											\
						uint16_t i;								\
						for(i = 0 ; i < n ; i++ ) WAIT_1MS();	\
						}

#define WAIT_1MS()	{uint32_t i;						\
					for(i = 0 ; i < (500000/350) ; i++ ){};	\
					}




void sd_spi_init_low_speed();
void sd_spi_init_high_speed();
void sd_spi_deinit();
ERROR_status sd_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
void sd_spi_cs_down();
void sd_spi_cs_up();

#endif
