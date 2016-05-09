



#include "sequencer.h"


sequencer_main_status_typedef G_seq_main_status;
int32_t G_timebase;

void seq_init(int32_t timebase){

	sequencer_button_init(timebase);
	sequencer_led_init(timebase);
	uart_init();
	G_seq_main_status = seq_main_status_init_stop;
	G_timebase = timebase;
}

void seq(){
	SEQ_BUTTON_push_type_typedef button;
	SEQ_LED_blink_action_typedef led_action;


/*
	//
	button = sequencer_button_get_push_type();
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

		sequencer_led_set_blink_action(led_action, button);
	}



	// Action de gestion des modes
	time += G_timebase;
	switch (G_seq_main_status){
				case seq_main_status_init_manip:
					// Configuration du capteur
					lsm9_driver_init();

					G_seq_main_status = seq_main_status_periodic_manip;
				break;

				case seq_main_status_periodic_manip:

					lsm9_driver_get_data(&data);
					sd_driver_fill_buffer(&data,time);
					sd_driver_bufferswitcher_emptying();
					// action periodique mode start/run

				break;
				case seq_main_status_init_stop:
					// Extinction capteur and co
					//lsm9_driver_deinit();
					G_seq_main_status = seq_main_status_periodic_stop;
				break;

				case seq_main_status_periodic_stop:

					// action periodique mode stop -> rien

				break;
				default:
					G_seq_main_status = seq_main_status_periodic_manip;
				break;
	}



	// Changement du mode courant
	if( button == SEQ_BUTTON_push_type_typedef_short_push ){

		G_seq_main_status = seq_main_status_init_manip;
	}else if( button == SEQ_BUTTON_push_type_typedef_two_short_push ){

		G_seq_main_status = seq_main_status_init_stop;
	}



	// Actionnement des leds
	sequencer_led_execute();
	*/
}
