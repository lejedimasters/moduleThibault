



#include "sequencer.h"


sequencer_main_status_typedef G_seq_main_status;
int32_t G_timebase;
int32_t G_time;
extern FATFS fs;


void seq_init(int32_t timebase){

	sequencer_button_init(timebase);
	sequencer_led_init(timebase);
	uart_init();
	G_seq_main_status = seq_main_status_init_stop;
	G_timebase = timebase;
	G_time = 0;
}

void seq(){
	SEQ_BUTTON_push_type_typedef button;
	SEQ_LED_blink_action_typedef led_action;
	lsm9_data_typedef	data;
	FRESULT res;

	// Incrementation du temps
	G_time += G_timebase;

	// Verification des boutons
	button = sequencer_button_get_push_type();
	// Si un type d'appui bouton a ete effectue, on assigne l'action led periodique a effectuer
	if( button != SEQ_BUTTON_push_type_typedef_no_push ){

		switch (button) {
			case SEQ_BUTTON_push_type_typedef_short_push:
				led_action = SEQ_LED_blink_action_manip;
			break;

			case SEQ_BUTTON_push_type_typedef_two_short_push:
				led_action = SEQ_LED_blink_action_idle;
			break;

			case SEQ_BUTTON_push_type_typedef_long_push:
				led_action = SEQ_LED_blink_action_reset;
			break;

			case SEQ_BUTTON_push_type_typedef_unknown:
				led_action = SEQ_LED_blink_action_error;
			break;

			default:

			break;
		}
		// Mise en place de l'action changeant le type de clignotement periodique de led et le type d'appui bouton effectue
		sequencer_led_set_blink_action(led_action, button);
	}


	// Vérification du changement de mode courant
	// Si une demande de changement de mode est effectue et que ce n'est pas le mode courant
	if( (button == SEQ_BUTTON_push_type_typedef_short_push)
			&& (G_seq_main_status != seq_main_status_periodic_manip) ){

		G_seq_main_status = seq_main_status_init_manip;

	}else if( (button == SEQ_BUTTON_push_type_typedef_two_short_push)
			&& (G_seq_main_status != seq_main_status_periodic_stop) ){

		G_seq_main_status = seq_main_status_init_stop;

	}else if( (button == SEQ_BUTTON_push_type_typedef_long_push)
			&& (G_seq_main_status != seq_main_status_init_reset) ){

		G_seq_main_status = seq_main_status_init_reset;
	}

	// Action de gestion des modes
	switch (G_seq_main_status){

				case seq_main_status_init_manip:
					// Configuration du capteur
					lsm9_driver_init( );
					G_timebase = 10;
					sequencer_button_init(G_timebase);
					sequencer_led_init(G_timebase);
					G_seq_main_status = seq_main_status_periodic_manip;
				break;

				case seq_main_status_periodic_manip:

					lsm9_driver_get_data(&data);
					sd_driver_fill_buffer(&data,G_time);
					sd_driver_bufferswitcher_emptying();
					// action periodique mode start/run

				break;

				case seq_main_status_init_stop:
					// Extinction capteur and co
/*
					lsm9_driver_deinit();
					G_timebase = 40;
					sequencer_button_init(G_timebase);
					sequencer_led_init(G_timebase);
*/
					G_seq_main_status = seq_main_status_periodic_stop;
				break;

				case seq_main_status_periodic_stop:

					// action periodique mode stop -> rien

				break;

				case seq_main_status_init_reset:
					// Reinit du pointeur d'adresse pour la carte SD en ouvrant le fichier
					while( res != FR_OK){
						res = pf_open("TEST.txt");
					}

					// Reinit du comptage du temps
					G_time = 0;

					G_seq_main_status = seq_main_status_init_stop;
				break;

				default:
					G_seq_main_status = seq_main_status_periodic_manip;
				break;
	}







	// Actionnement des leds
	sequencer_led_execute();

}
