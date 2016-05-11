/*
 *  Théo Folin
 *  2016
 * 	sequencer_led.c
 *
 * A REFAIRE
 *
 *
 * */


#include "sequencer_led.h"


static uint32_t G_timeBase_ms;
static uint32_t G_timeCounter_ms;
static SEQ_LED_blink_action_typedef G_current_blink_action;
static SEQ_BUTTON_push_type_typedef G_button_push_type;
static uint32_t G_new_blink_action;

static uint32_t sequencer_led_get_time_cycle( void );
static uint32_t sequencer_led_get_blink_time( void );
static void sequencer_led_blink_button_seq( void );
static void sequencer_led_blink_mode_seq( void );

void sequencer_led_init( uint32_t timeBase_ms, SEQ_LED_blink_action_typedef blink_action ){

	driver_led_init();
	G_timeBase_ms = timeBase_ms;
	G_timeCounter_ms = 0;

	G_current_blink_action = blink_action;
	G_button_push_type = SEQ_BUTTON_push_type_typedef_no_push;
}

void sequencer_led_set_blink_action( SEQ_LED_blink_action_typedef blink_action, SEQ_BUTTON_push_type_typedef button_push_type ){


	if( button_push_type !=  SEQ_BUTTON_push_type_typedef_no_push ){ // Dans le cas d'un appui bouton, on fait l'affichage led dedié au bouton puis l'affichage de l'action
		if( G_current_blink_action != blink_action){
			/* nouvelle action, on relance complétement le sequencer*/
			G_current_blink_action = blink_action;
			G_button_push_type = button_push_type;
			G_timeCounter_ms = 0;
			driver_led_reset();
			G_new_blink_action = 1;
		}
	}
	else{
		if( G_current_blink_action != SEQ_LED_blink_action_no_switch){	// dans le cas d'un switch d'etat sans action utilisateur, on fait juste l'affichage de l'action
			/* nouvelle action, on relance complétement le sequencer*/
			G_current_blink_action = blink_action;
			G_timeCounter_ms = 0;
			driver_led_reset();
		}
	}
}

void sequencer_led_execute( void ){
	uint32_t time_ms;
//	uint32_t time_tempo_ms;




	G_timeCounter_ms += G_timeBase_ms;
	time_ms = sequencer_led_get_time_cycle();
	if( G_timeCounter_ms > time_ms ){
		G_timeCounter_ms = 0;
	}


	/* Clignotement de switch d'etat */
	if( G_new_blink_action == 1 ){

		sequencer_led_blink_button_seq();
	}/* Clignotement de l'etat actuel  lorsque le switch d'etat est fini */
	else{

		sequencer_led_blink_mode_seq();
	}


}

static uint32_t sequencer_led_get_time_cycle( void ){
	uint32_t time_cyle;

	if( G_new_blink_action ){
		time_cyle = TOTAL_TIME_BUTTON;
	}
	else{
		switch (G_current_blink_action) {
			case SEQ_LED_blink_action_manip:
				time_cyle = BLINK_TIME_CYCLE_MANIP_MS;
				break;
			case SEQ_LED_blink_action_idle:
				time_cyle = BLINK_TIME_CYCLE_IDLE_MS;
				break;
			case SEQ_LED_blink_action_reset:
				time_cyle = BLINK_TIME_CYCLE_RESET_MS;
				break;
			case SEQ_LED_blink_action_error:
				time_cyle = BLINK_TIME_CYCLE_ERROR_MS;
				break;
			default:
				time_cyle = BLINK_TIME_CYCLE_ERROR_MS;
				break;
		}
	}

	time_cyle += G_timeBase_ms;
	return time_cyle;
}


static uint32_t sequencer_led_get_blink_time( void ){
	uint32_t blink_time;

	switch (G_current_blink_action) {
		case SEQ_LED_blink_action_manip:
			blink_time = BLINK_ON_DEFAULT_VALUE_MS;
			break;
		case SEQ_LED_blink_action_idle:
			blink_time = BLINK_ON_DEFAULT_VALUE_MS;
			break;
		case SEQ_LED_blink_action_reset:
			blink_time = BLINK_ON_DEFAULT_VALUE_MS;
			break;
		case SEQ_LED_blink_action_error:
			blink_time = BLINK_ON_ERROR_VALUE_MS;
			break;
		default:
			blink_time = BLINK_ON_ERROR_VALUE_MS;
			break;
	}

	return blink_time;
}


static uint32_t sequencer_led_get_blink_button_time( void ){
	uint32_t blink_time;

	switch (G_button_push_type) {
		case SEQ_BUTTON_push_type_typedef_short_push:
			blink_time = BLINK_ON_DEFAULT_VALUE_MS;
			break;
		case SEQ_BUTTON_push_type_typedef_two_short_push:
			blink_time = BLINK_ON_DEFAULT_VALUE_MS;
			break;
		case SEQ_BUTTON_push_type_typedef_long_push:
			blink_time = BLINK_ON_LONG_VALUE_MS;
			break;
		default:
			blink_time = BLINK_ON_ERROR_VALUE_MS;
			break;
	}

	return blink_time;
}

static void sequencer_led_blink_button_seq( void ){
	uint32_t time_ms;


	// clignotement bouton
	time_ms = sequencer_led_get_blink_button_time();

	/* Temporisation après le switch de type de clignotement*/
	if( G_timeCounter_ms < TEMPO_SWITCH_ACTION_MS ){
		driver_led_reset();
	} /* Clignotement correspondant au type de bouton afin de savoir si notre appui correspond à ce qu'on voulait */
	else if( G_timeCounter_ms < (TEMPO_SWITCH_ACTION_MS + BLINK_TIME_CYCLE_BUTTON_MS) ){

		if( G_button_push_type == SEQ_BUTTON_push_type_typedef_two_short_push ){ // Sequencement particuliers pour le double appui bouton
			if( G_timeCounter_ms < (TEMPO_SWITCH_ACTION_MS + time_ms) ){ /* Mode on du mode de clignotement */

				driver_led_set();
			}else if( G_timeCounter_ms < (TEMPO_SWITCH_ACTION_MS + 2*time_ms) ){	/* Mode off du mode de clignotement */

				driver_led_reset();
			}else if( G_timeCounter_ms < (TEMPO_SWITCH_ACTION_MS + 3*time_ms) ){	/* Mode off du mode de clignotement */

				driver_led_set();
			}else{	/* Mode off du mode de clignotement */

				driver_led_reset();
			}
		}else{

			if( G_timeCounter_ms < (TEMPO_SWITCH_ACTION_MS + time_ms) ){ /* Mode on du mode de clignotement */

				driver_led_set();
			}
			else{	/* Mode off du mode de clignotement */

				driver_led_reset();
			}
		}




	}/* Fin du clignotement de switch */
	else if( G_timeCounter_ms < TOTAL_TIME_BUTTON ){

		driver_led_reset();
	}
	else{
		driver_led_reset();
		G_new_blink_action = 0;
		G_button_push_type = SEQ_BUTTON_push_type_typedef_no_push;
	}
}
static void sequencer_led_blink_mode_seq( void ){
	uint32_t time_ms;

	time_ms = sequencer_led_get_blink_time();

	if( G_timeCounter_ms < time_ms ){ /* Mode on du mode de clignotement */

		driver_led_set();
	}
	else{	/* Mode off du mode de clignotement */

		driver_led_reset();
	}
}
