
#ifndef SEQUENCER_H
#define SEQUENCER_H


#include "sequencer_button.h"
#include "sequencer_led.h"
#include "uart.h"
#include "pff.h"


#define SCHEDULER_ON	0
#define SCHEDULER() 	seq()

void seq( void );
void seq_init( int32_t timebase );


typedef enum
{
	seq_main_status_init_manip,
	seq_main_status_periodic_manip,
	seq_main_status_init_stop,
	seq_main_status_periodic_stop,
	seq_main_status_init_reset,
	seq_main_status_periodic_reset
}sequencer_main_status_typedef;


#endif
