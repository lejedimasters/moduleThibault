/*
 *  Théo Folin
 *  2016
 * 	driver_button.c
 *
 * A REFAIRE
 *
 *
 * */


#include "driver_button.h"


BUTTON_status_typedef driver_button_get_status(){
	BUTTON_status_typedef current_button_status;

	current_button_status = driver_button_get_pin_state();


	/* Detection d'un front */
	if( current_button_status.value != G_last_button_status.value){

		/* Detection front montant */
		if( G_last_button_status.value == BUTTON_value_typedef_RESET ){

			current_button_status.edge = BUTTON_edge_typedef_rising_edge;

		}
		else{ /* Front descendant */

			current_button_status.edge = BUTTON_edge_typedef_falling_edge;
		}
	}
	else{/* Aucun front */

		current_button_status.edge = BUTTON_edge_typedef_no_edge;
	}



	/* Mise à jour du status precedent */
	G_last_button_status.edge = current_button_status.edge;
	G_last_button_status.value = current_button_status.value;

	return current_button_status;
}



int32_t driver_button_init(){

	GPIO_InitTypeDef GPIO_InitStruct;

//	/* GPIO Ports Clock Enable */
//	__GPIOA_CLK_ENABLE();
//
//	/* Initialisation de la pin du bouton */
//	GPIO_InitStruct.Pin = GPIO_PIN_5;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* GPIO Ports Clock Enable */
	  __GPIOC_CLK_ENABLE();

	/* Initialisation de la pin du bouton */
	  /*Configure GPIO pin : PC13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	/* Initialisation du bouton status */
	G_last_button_status = driver_button_get_pin_state();

	return 0;
}


BUTTON_status_typedef	driver_button_get_pin_state(){
	BUTTON_status_typedef button_value;

	button_value.value = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);
	button_value.edge = BUTTON_edge_typedef_no_edge;
	return button_value;
}





