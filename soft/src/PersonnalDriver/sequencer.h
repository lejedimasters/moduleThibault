
#ifndef SEQUENCER_H
#define SEQUENCER_H


#include "sequencer_button.h"
#include "sequencer_led.h"
#include "uart.h"



#define SCHEDULER_INT_MS	10
#define SCHEDULER_ON	1
#define SCHEDULER() 	seq()

void seq( void );
void seq_init( void );
SEQ_LED_blink_action_typedef translate_pushType_to_ledAction( SEQ_BUTTON_push_type_typedef button_push);

#endif
