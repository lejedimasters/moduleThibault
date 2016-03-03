/*
 *  Théo Folin
 *  2016
 * 	sd_driver.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef SD_DRIVER_H
#define SD_DRIVER_H

#include "stm32f4xx_hal.h"
#include "sd_spi.h"
//#include "ff.h"
#include "error.h"
#include "lsm9_driver.h"


#define NB_SD_BUFFER 	3
#define DATA_CMD_SIZE	512

/*
typedef enum
{
	buffer_status_typedef_empty,
	buffer_status_typedef_filling,
	buffer_status_typedef_filled
}buffer_status_typedef;

typedef struct
{
	uint8_t			buffer[DATA_CMD_SIZE];
	buffer_status 	status;
	uint16_t 		index;

}sd_buffer_typedef;

typedef struct
{
	sd_buffer_typedef	buffer_switch[NB_SD_BUFFER];
	uint8_t 			currentBuffer;
}sd_buffer_switcher_typedef;

*/
void sd_driver_init();
//ErrorStatus sd_driver_fill_buffer(lsm9_data_typedef *data, uint32_t time_ms);


#endif
