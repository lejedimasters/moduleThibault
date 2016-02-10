



#include "sequencer.h"


void seq_init(){

	sequencer_button_init(SCHEDULER_INT_MS);
	sequencer_led_init(SCHEDULER_INT_MS);
	uart_init();
}

void seq(){

	/* BEGIN MODE ACTION */
		/* READ SENSOR / WRITE SD CARD */
		/* ERASE SD CARD */
		/* IDLE */
	/* END MODE ACTION */


	/* BEGIN TEST SWITCH MODE */

	/* END TEST SWITCH MODE */


	SEQ_BUTTON_push_type_typedef button;
	SEQ_LED_blink_action_typedef led_action;

	sequencer_led_execute();
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

}
