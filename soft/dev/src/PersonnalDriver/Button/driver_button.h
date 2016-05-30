/*
 *  Théo Folin
 *  2016
 * 	driver_button.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef DRIVER_BUTTON_H
#define DRIVER_BUTTON_H

#include "stm32f4xx_hal.h"
#include "error.h"
#include "board.h"


typedef enum
{
	BUTTON_edge_typedef_no_edge = 0,
	BUTTON_edge_typedef_falling_edge,
	BUTTON_edge_typedef_rising_edge
}BUTTON_edge_typedef;

typedef enum
{
	BUTTON_value_typedef_SET = GPIO_PIN_RESET,		// bouton enfonce
	BUTTON_value_typedef_RESET = GPIO_PIN_SET		//
}BUTTON_value_typedef;

typedef struct
{
	BUTTON_value_typedef	value;
	BUTTON_edge_typedef		edge;
	//ERROR_status			error;
}BUTTON_status_typedef;

BUTTON_status_typedef 	G_last_button_status;


BUTTON_status_typedef 	driver_button_get_status();
int32_t 				driver_button_init();
BUTTON_status_typedef	driver_button_get_pin_state();

#endif
