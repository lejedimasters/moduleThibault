
#ifndef SEQUENCER_H
#define SEQUENCER_H


#include "sequencer_button.h"
#include "sequencer_led.h"
#include "uart.h"



#define SCHEDULER_INT_MS	10
#define SCHEDULER_ON	0
#define SCHEDULER() 	seq()

void seq( void );
void seq_init( void );


#endif
