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
	uint8_t i;

	for( i = 0 ; i < 100 ; i++ ){

		temp_buff[i] = 'a';
	}


	sprintf((char*)temp_buff, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n\r",
			(int)time_ms,
			(int)data->accelerometry.X, 	(int)data->accelerometry.Y, 	(int)data->accelerometry.Z,
			(int)data->gyroscope.X, 		(int)data->gyroscope.Y, 		(int)data->gyroscope.Z,
			(int)data->magnotemeter.X, 	(int)data->magnotemeter.Y, 	(int)data->magnotemeter.Z
			);



	return ERROR_status_NOERROR;
}
