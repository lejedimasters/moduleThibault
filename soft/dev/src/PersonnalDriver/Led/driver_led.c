/*
 *  Théo Folin
 *  2016
 * 	driver_led.c
 *
 * A REFAIRE
 *
 *
 * */


#include "driver_led.h"


void driver_led_init( void ){
	  GPIO_InitTypeDef GPIO_InitStruct;


	  __GPIOA_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_LED;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	  HAL_GPIO_Init(GPIO_BLOCK_LED, &GPIO_InitStruct);
}

void driver_led_set( void ){
	/*GPIOA.BSRR = GPIO_PIN_5;*/
	HAL_GPIO_WritePin(GPIO_BLOCK_LED, GPIO_PIN_LED,  GPIO_PIN_RESET );
}

void driver_led_reset( void ){
	/*GPIOA.BSRR = (uint32_t)GPIO_PIN_5 << 16;*/
	HAL_GPIO_WritePin(GPIO_BLOCK_LED, GPIO_PIN_LED,  GPIO_PIN_SET);
}

void driver_led_toggle( void ){
	/*GPIOA.ODR ^= GPIO_PIN_5;*/
	HAL_GPIO_TogglePin(GPIO_BLOCK_LED, GPIO_PIN_LED);
}
