/*
 *  Théo Folin
 *  2016
 * 	driver_led.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef DRIVER_LED_H
#define DRIVER_LED_H


#include "stm32f4xx_hal.h"
#include "error.h"
#include "board.h"

void driver_led_init( void );
void driver_led_set( void );
void driver_led_reset( void );
void driver_led_toggle( void );



#endif
