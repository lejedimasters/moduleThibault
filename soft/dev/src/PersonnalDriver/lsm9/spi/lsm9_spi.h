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
#include "board.h"



void lsm9_spi_init( int nb );
ERROR_status lsm9_spi_transmit_receive_XG(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
ERROR_status lsm9_spi_transmit_receive_M(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

#endif
