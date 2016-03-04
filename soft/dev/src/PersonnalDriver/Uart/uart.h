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

void uart_init( void );
void uart_send( int8_t *tab, uint16_t size );
uint32_t uart_receive( uint8_t *tab, uint16_t size );




#endif
