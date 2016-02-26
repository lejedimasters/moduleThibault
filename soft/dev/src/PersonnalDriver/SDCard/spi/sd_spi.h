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

void sd_spi_init();
ERROR_status sd_spi_transmit_receive_G(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
void sd_spi_cs_down();
void sd_spi_cs_up();

#endif
