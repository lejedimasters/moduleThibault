/*
 *  Théo Folin
 *  2016
 * 	lsm9_spi.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef LSM9_SPI_H
#define LSM9_SPI_H

#include "stm32f4xx_hal.h"
#include "error.h"


void lsm9_spi_init();
ERROR_status lsm9_spi_transmit_receive_G(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
ERROR_status lsm9_spi_transmit_receive_XM(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

#endif
