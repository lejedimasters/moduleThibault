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
#include "string.h"
#include "uart.h"

sd_buffer_switcher_typedef buffer_switcher;

extern FATFS fs;




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
	uint16_t i,y;


	// Initialisation du triple buffer
	buffer_switcher.currentBuffer = 0;
	for( i = 0 ; i < NB_SD_BUFFER ; i++ ){

		buffer_switcher.buffer_switch[i].index = 0;
		buffer_switcher.buffer_switch[i].status = buffer_status_typedef_empty;

		for( y = 0 ; y < DATA_CMD_SIZE ; y++ ){
			buffer_switcher.buffer_switch[i].buffer[y] = 0;
		}
	}


	//


}

ErrorStatus sd_driver_fill_buffer(lsm9_data_typedef *data, uint32_t time_ms){
	uint8_t temp_buff[100]={0},currentBuffer;
	uint16_t remainingData=0;



	sprintf((char*)temp_buff, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\r\n",
			(int)time_ms,
			(int)data->accelerometry.X, 	(int)data->accelerometry.Y, 	(int)data->accelerometry.Z,
			(int)data->gyroscope.X, 		(int)data->gyroscope.Y, 		(int)data->gyroscope.Z,
			(int)data->magnotemeter.X, 	(int)data->magnotemeter.Y, 	(int)data->magnotemeter.Z
			);


	sd_driver_write_to_bufferswitcher(temp_buff, &remainingData);
	currentBuffer = buffer_switcher.currentBuffer;

	// Si toutes les donnees n'ont pas ete ecrites dans le buffer courant
	if( remainingData > 0 ){
		// On met le buffer courant en status rempli
		buffer_switcher.buffer_switch[currentBuffer].status = buffer_status_typedef_filled;

		// On change l'index du buffer
		buffer_switcher.currentBuffer++;
		if( buffer_switcher.currentBuffer > 2 ){
			buffer_switcher.currentBuffer = 0;
		}
		currentBuffer = buffer_switcher.currentBuffer;

		if( buffer_switcher.buffer_switch[currentBuffer].status != buffer_status_typedef_empty ){
			return -1;
		}

		sd_driver_write_to_bufferswitcher(temp_buff, &remainingData);

		if( remainingData != 0 ){
			return -2;
		}

	}


	return ERROR_status_NOERROR;
}




ErrorStatus sd_driver_write_to_bufferswitcher( uint8_t *temp_buff, uint16_t *remainingData){
	uint8_t currentBuffer;
	uint16_t i,cptFor,writenData = 0,dataToWrite;


	currentBuffer = buffer_switcher.currentBuffer;
	dataToWrite = strlen((char*)temp_buff);

	// Verification si le buffer courant peut acceuillir toutes les donnees
	// S'il y a trop de donnees, on definit fixe l'index max à atteindre à la taille du buffer
	// Sinon, on fixe l'index atteignable du buffer courant
	if( (dataToWrite + buffer_switcher.buffer_switch[currentBuffer].index) > DATA_CMD_SIZE ){

		cptFor = DATA_CMD_SIZE;
	}else{

		if( remainingData[0] == 0 ){
			cptFor = dataToWrite + buffer_switcher.buffer_switch[currentBuffer].index;
		}
		else{
			cptFor = remainingData[0];
		}


	}

	// Remplissage du buffer courant juqu'a l'index definit precedemmment
	if( remainingData[0] != 0 ){
		writenData = dataToWrite - remainingData[0];
	}
	else{
		writenData = 0;
	}


	for( i = buffer_switcher.buffer_switch[currentBuffer].index ; i < cptFor ; i++){

		buffer_switcher.buffer_switch[currentBuffer].buffer[i] = temp_buff[writenData];
		writenData++;
	}

	remainingData[0] = dataToWrite - writenData;

	// Mise a jour de l'index dans la structure du buffer
	buffer_switcher.buffer_switch[currentBuffer].index = i-1;

	return ERROR_status_NOERROR;
}

ErrorStatus sd_driver_bufferswitcher_emptying(){
	uint8_t i, currentBufferFilled = 255;
	uint32_t adress;



	for( i = 0 ; i < NB_SD_BUFFER ; i++ ){

		if( buffer_switcher.buffer_switch[i].status == buffer_status_typedef_filled ){

			if( currentBufferFilled != 255 ){
				// Deux buffer plein, bug a surveiller
				return -1;
			}
			currentBufferFilled = i;
		}
	}


	if( currentBufferFilled == 255 ){
		return ERROR_status_NOERROR;
	}

	//buffer_switcher.buffer_switch[currentBufferFilled].buffer

#if 0
	uart_send((int8_t*)buffer_switcher.buffer_switch[currentBufferFilled].buffer,DATA_CMD_SIZE);
#else


    adress = fs.database++;
    adress *=512;
    sd_driver_cc2541_write(adress , 512 , (uint8_t*)buffer_switcher.buffer_switch[currentBufferFilled].buffer);


#endif

	buffer_switcher.buffer_switch[currentBufferFilled].status = buffer_status_typedef_empty;
	buffer_switcher.buffer_switch[currentBufferFilled].index = 0;

	return ERROR_status_NOERROR;
}















