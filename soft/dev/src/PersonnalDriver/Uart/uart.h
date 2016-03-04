/*
 *  Théo Folin
 *  2016
 * 	uart.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"
#include "error.h"
#include "lsm9_driver.h"


void uart_init( void );
void uart_send( int8_t *tab, uint16_t size );
uint32_t uart_receive( uint8_t *tab, uint16_t size );


ERROR_status uart_send_data_ASCII( lsm9_data_typedef *data);
ERROR_status uart_send_data_bytes( lsm9_data_typedef *data);



#endif
