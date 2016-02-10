/*
 *  Théo Folin
 *  2016
 * 	sequencer_button.c
 *
 * A REFAIRE
 *
 *
 * */

#include "sequencer_button.h"

/* PROTOTYPE PRIVE */
static void sequencer_button_reinit( BUTTON_status_typedef *currentButtonStatus);
static SEQ_BUTTON_push_type_typedef sequencer_button_detect_push_type(  BUTTON_status_typedef *currentButtonStatus );

/* GLOBALE PRIVE */
static int32_t G_acquisition_time_counter;
static int32_t G_push_time_counter;
static int32_t G_timebase;
static SEQ_BUTTON_push_type_typedef G_old_push_type;




/** FONCTION **/

/******************************************************/
/** int32_t sequencer_button_init(uint32_t timebase) **/
/******************************************************/
int32_t sequencer_button_init(uint32_t timebase){

	/* Erreur a definir */
#warning TO DEFINE
	if( timebase < MIN_TIME_BASE){

		return -1;
	}
	if( timebase > MAX_TIME_BASE ){

		return -1;
	}
	G_acquisition_time_counter = 0;
	G_push_time_counter = 0;
	G_timebase = timebase;
	driver_button_init();
	return 0;
}



/*******************************************************************/
/** SEQ_BUTTON_push_type_typedef sequencer_button_get_push_type() **/
/*******************************************************************/
SEQ_BUTTON_push_type_typedef sequencer_button_get_push_type(){
	SEQ_BUTTON_push_type_typedef currentPushType;
	BUTTON_status_typedef currentButtonStatus;


	currentPushType = SEQ_BUTTON_push_type_typedef_no_push;
	currentButtonStatus = driver_button_get_status();

	if( G_acquisition_time_counter > 0 ){

		G_acquisition_time_counter += G_timebase;

		if( currentButtonStatus.value == BUTTON_value_typedef_SET ){
			G_push_time_counter += G_timebase;
		}

		/* Timeout sur un temps d'appui trop long */
		if( G_acquisition_time_counter > MAX_ACQUISITION_TIME_MS ){


			if( G_push_time_counter == G_acquisition_time_counter ){
				sequencer_button_reinit(&currentButtonStatus);
				currentPushType = SEQ_BUTTON_push_type_typedef_long_push;
			}
			else{
				sequencer_button_reinit(&currentButtonStatus);
				currentPushType = SEQ_BUTTON_push_type_typedef_no_push;
			}
		}
		else{
			/* Detection du type d'appui */
			currentPushType = sequencer_button_detect_push_type(&currentButtonStatus);
		}




		/* detection du double appui */
		if( currentPushType == SEQ_BUTTON_push_type_typedef_short_push ){
			if( G_old_push_type == SEQ_BUTTON_push_type_typedef_short_push ){
				currentPushType = SEQ_BUTTON_push_type_typedef_two_short_push;
				sequencer_button_reinit(&currentButtonStatus);
			}
			else{
				currentPushType = SEQ_BUTTON_push_type_typedef_no_push;
				G_old_push_type = SEQ_BUTTON_push_type_typedef_short_push;
			}

		}

		if( G_old_push_type == SEQ_BUTTON_push_type_typedef_short_push ){

			if( G_acquisition_time_counter > MAX_UPTIME_SHORT_PUSH ){
				currentPushType = SEQ_BUTTON_push_type_typedef_short_push;
				sequencer_button_reinit(&currentButtonStatus);
			}

		}


	}

	if( currentButtonStatus.edge == BUTTON_edge_typedef_rising_edge ){

		// On lance le compteur du temps d'acquisition
		if( G_acquisition_time_counter == 0 ){
			G_acquisition_time_counter += G_timebase;
			G_push_time_counter += G_timebase;
		}
	}

;




	return currentPushType;
}

/**************************************************************************************/
/** static void sequencer_button_reinit( BUTTON_status_typedef *currentButtonStatus) **/
/**************************************************************************************/
static void sequencer_button_reinit( BUTTON_status_typedef *currentButtonStatus){

	currentButtonStatus->edge = BUTTON_edge_typedef_no_edge;
	G_old_push_type = SEQ_BUTTON_push_type_typedef_no_push;
	G_acquisition_time_counter = 0;
	G_push_time_counter = 0;

}
/**************************************************************************************************************************/
/** static SEQ_BUTTON_push_type_typedef sequencer_button_detect_push_type(  BUTTON_status_typedef *currentButtonStatus ) **/
/**************************************************************************************************************************/
static SEQ_BUTTON_push_type_typedef sequencer_button_detect_push_type(  BUTTON_status_typedef *currentButtonStatus ){
	SEQ_BUTTON_push_type_typedef currentPushType2;

	if( (currentButtonStatus->edge == BUTTON_edge_typedef_falling_edge) && ( G_acquisition_time_counter > 0 ) ){



		if( G_push_time_counter < MIN_UPTIME_SHORT_PUSH ){
			currentPushType2 = SEQ_BUTTON_push_type_typedef_unknown;
		}
		else if( G_push_time_counter < MAX_UPTIME_SHORT_PUSH ){
			currentPushType2 = SEQ_BUTTON_push_type_typedef_short_push;
		}
		else if( G_push_time_counter < MIN_UPTIME_LONG_PUSH ){
			currentPushType2 = SEQ_BUTTON_push_type_typedef_unknown;
		}
		else if( G_push_time_counter < MAX_UPTIME_LONG_PUSH ){
			currentPushType2 = SEQ_BUTTON_push_type_typedef_long_push;
		}
		else{
			currentPushType2 = SEQ_BUTTON_push_type_typedef_unknown;
		}
		G_push_time_counter = 0;

		if( currentPushType2 == SEQ_BUTTON_push_type_typedef_unknown ){
			G_acquisition_time_counter = 0;
		}
	}

	return currentPushType2;
}




