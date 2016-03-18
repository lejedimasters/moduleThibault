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
ERROR_status dummyclock();


ERROR_status sd_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
void sd_spi_cs_down();
void sd_spi_cs_up();

uint8_t sd_spi_read_R7_or_R3( uint8_t *responseR7 );
uint8_t sd_spi_read_R1( void );
uint8_t sd_spi_makeCRC7(uint8_t *buffer, uint8_t length);
void sd_spi_send_cmd( uint8_t command, uint32_t argument );
void sd_spi_send_acmd( uint8_t command, uint32_t argument );
void sd_spi_send_data_packet(uint32_t data_token , uint16_t length , const uint8_t *data);
void sd_spi_read_data_packet( uint32_t data_token , uint16_t length , uint8_t *data);
void sd_spi_send_stop( void );
#endif
