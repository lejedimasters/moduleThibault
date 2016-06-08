/*
 *  Théo Folin
 *  2016
 * 	sequencer_button.h
 *
 * A REFAIRE
 *
 *
 * */
#ifndef SEQUENCER_BUTTON_H
#define SEQUENCER_BUTTON_H

#include "stm32f4xx_hal.h"
#include "error.h"
#include "driver_button.h"

typedef enum
{
	SEQ_BUTTON_push_type_typedef_no_push = 0,
	SEQ_BUTTON_push_type_typedef_short_push,
	SEQ_BUTTON_push_type_typedef_two_short_push,
	SEQ_BUTTON_push_type_typedef_long_push,
	SEQ_BUTTON_push_type_typedef_unknown
}SEQ_BUTTON_push_type_typedef;



int32_t	sequencer_button_init(uint32_t timebase);
SEQ_BUTTON_push_type_typedef	sequencer_button_get_push_type();


#define MAX_ACQUISITION_TIME_MS		6000	// Temps d'acquisition maximal d'une série d'appui bouton. Au dela, timeout sur l'appui bouton
#define MIN_UPTIME_SHORT_PUSH		30		// Temps minimal de l'état haut pour que l'appui soit considéré comme un appui court
#define MAX_UPTIME_SHORT_PUSH		2000		// Temps maximal de l'état haut pour que l'appui soit considéré comme un appui court
#define MIN_UPTIME_LONG_PUSH		5000	// Temps minimal de l'état haut pour que l'appui soit considéré comme un appui long
#define MAX_UPTIME_LONG_PUSH		6000	// Temps maximal de l'état haut pour que l'appui soit considéré comme un appui long

#define MIN_TIME_BASE				1
#define MAX_TIME_BASE				40


#if MAX_UPTIME_LONG_PUSH > MAX_ACQUISITION_TIME_MS
	#error temps max tolere pour un appui long trop grand
#endif







#endif
