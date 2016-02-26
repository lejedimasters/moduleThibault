/*
 *  Théo Folin
 *  2016
 * 	sd_driver.c
 *
 * A REFAIRE
 *
 *
 * */

#include "sd_driver.h"


/** \fn void sd_driver_init( )
 * \param[in] 
 * \param[out] 
 * \author T.Folin
 * \test
 * \brief	
 * \deprecated
 *            SLD_
 */
void sd_driver_init(){

}

ErrorStatus sd_driver_fill_buffer(lsm9_data_typedef *data, uint32_t time_ms){
	uint8_t temp_buff[100]={'a'};
	uint16_t i,y=0,cptFor;
	uint16_t str_size;

	sd_buffer_switcher_typedef buffer_switcher;

	sprintf((char*)temp_buff, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n\r",
			(int)time_ms,
			(int)data->accelerometry.X, 	(int)data->accelerometry.Y, 	(int)data->accelerometry.Z,
			(int)data->gyroscope.X, 		(int)data->gyroscope.Y, 		(int)data->gyroscope.Z,
			(int)data->magnotemeter.X, 	(int)data->magnotemeter.Y, 	(int)data->magnotemeter.Z
			);



	str_size = strlen(temp_buff);

	if( (str_size + buffer_switcher.buffer[buffer_switcher.currentBuffer].index) > DATA_CMD_SIZE ){

		cptFor = DATA_CMD_SIZE;
	}else{

		cptFor = str_size + buffer_switcher.buffer[buffer_switcher.currentBuffer].index;
	}


	for( i = buffer_switcher.buffer[buffer_switcher.currentBuffer].index ; i < cptFor ; i++){

		buffer_switcher.buffer_switch[buffer_switcher.currentBuffer].buffer[i] = temp_buff[y];
		y++;
	}
	buffer_switcher.buffer[buffer_switcher.currentBuffer].index = i-1;

	if( y < str_size ){
		buffer_switcher.buffer_switch[buffer_switcher.currentBuffer].status = buffer_status_typedef_filled;

		buffer_switcher.currentBuffer++;
		if( buffer_switcher.currentBuffer > 3 ){
			buffer_switcher.currentBuffer = 0;
		}

		if( (str_size + buffer_switcher.buffer[buffer_switcher.currentBuffer].index) > DATA_CMD_SIZE ){

			cptFor = DATA_CMD_SIZE;
		}else{

			cptFor = str_size + buffer_switcher.buffer[buffer_switcher.currentBuffer].index;
		}
		for( i = buffer_switcher.buffer[buffer_switcher.currentBuffer].index ; i < cptFor ; i++){

			buffer_switcher.buffer_switch[buffer_switcher.currentBuffer].buffer[i] = temp_buff[y];
			y++;
		}
		buffer_switcher.buffer[buffer_switcher.currentBuffer].index = i-1;

	}


	return ERROR_status_NOERROR;
}

















