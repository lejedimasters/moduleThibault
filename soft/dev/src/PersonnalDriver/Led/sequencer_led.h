/*
 *  Théo Folin
 *  2016
 * 	driver_led.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef SEQUENCER_LED_H
#define SEQUENCER_LED_H

#include "stm32f4xx_hal.h"
#include "error.h"
#include "driver_led.h"
#include "sequencer_button.h"

/* Enumeration du clignotement pour chaque type de mode */
typedef enum
{
	SEQ_LED_blink_action_manip = 0,
	SEQ_LED_blink_action_idle,
	SEQ_LED_blink_action_reset,
	SEQ_LED_blink_action_error,
	SEQ_LED_blink_action_no_switch
}SEQ_LED_blink_action_typedef;


void sequencer_led_init( uint32_t timeBase_ms, SEQ_LED_blink_action_typedef blink_action  );
void sequencer_led_set_blink_action( SEQ_LED_blink_action_typedef blink_action, SEQ_BUTTON_push_type_typedef button_push_type  );
void sequencer_led_execute( void );



#define BLINK_ON_DEFAULT_VALUE_MS	100
#define BLINK_ON_LONG_VALUE_MS		900
#define BLINK_ON_ERROR_VALUE_MS		500

#define BLINK_TIME_CYCLE_MANIP_MS	1000
#define BLINK_TIME_CYCLE_IDLE_MS	10000
#define BLINK_TIME_CYCLE_RESET_MS	200
#define BLINK_TIME_CYCLE_ERROR_MS	1000

#define BLINK_TIME_CYCLE_BUTTON_MS	1000
#define TEMPO_SWITCH_ACTION_MS		1000
#define TOTAL_TIME_BUTTON			(2*TEMPO_SWITCH_ACTION_MS + BLINK_TIME_CYCLE_BUTTON_MS)



#endif
