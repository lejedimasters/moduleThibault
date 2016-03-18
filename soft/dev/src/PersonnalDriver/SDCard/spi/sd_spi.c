/*
 *  Théo Folin
 *  2016
 * 	sd_spi.c
 *
 * A REFAIRE
 *
 *
 * */

#include "sd_spi.h"

SPI_HandleTypeDef hspi1;
uint8_t buffer[515];
/** \fn void sd_spi_deinit( )
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_deinit(){

	HAL_SPI_MspDeInit(&hspi1);

}


/** \fn void sd_spi_init( )
 * \param[in] 
 * \param[out] 
 * \author T.Folin
 * \test
 * \brief	
 * \deprecated
 *            SLD_
 */
void sd_spi_init_low_speed(){
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	/* Initialisation du spi*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;

	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;

//	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
//	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;

//	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
//	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;

//	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
//	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;

	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; 	// 84MHz/ 256
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi1.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi1);


	/* PIN CS XM */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/** \fn void sd_spi_init( )
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_init_high_speed(){
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	/* Initialisation du spi*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; 	// 84MHz / 2
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi1.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi1);


	/* PIN CS XM */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/** \fn void
 * \param[in] 
 * \param[out] 
 * \author T.Folin
 * \test
 * \brief	
 * \deprecated
 *            SLD_
 */
ERROR_status sd_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){
	sd_spi_cs_down();
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, Size, 0xFFFF);
	sd_spi_cs_up();
	return ERROR_status_NOERROR;
}


ERROR_status dummyclock(){
	uint8_t tab[1] = {0xFF},i;


	for( i = 0 ; i < 80 ; i++ ){
		HAL_SPI_TransmitReceive(&hspi1, tab, tab, 1, 0xFFFF);
	}



	return ERROR_status_NOERROR;
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_cs_down(){

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_cs_up(){

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );
}


/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_send_cmd( uint8_t command, uint32_t argument )
{
	uint8_t buffer_to_write[6];
	//uint8_t buffer_to_read[6];
	//calcul the command to write
	buffer_to_write[0] = 0x40 | command;
	buffer_to_write[1] = (uint8_t)(argument >> 24);
	buffer_to_write[2] = (uint8_t)(argument >> 16);
	buffer_to_write[3] = (uint8_t)(argument >> 8);
	buffer_to_write[4] = (uint8_t)(argument);
	buffer_to_write[5] =  sd_spi_makeCRC7(buffer_to_write , 5);

	// write the commande on SPI
	sd_spi_transmit_receive(buffer_to_write, buffer_to_write, 6);
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
uint8_t sd_spi_makeCRC7(uint8_t *buffer, uint8_t length)
{
    uint8_t crc = 0;
    uint8_t data;
    uint8_t packet[10];
    uint8_t i;
    uint8_t a;

    for(i = 0;i < length; i++)
    {
        packet[i] = buffer[i];
    }

    for (a=0;a<5;a++) //Loop through the packet array starting at packet[0]
    {
        data=packet[a];// Loop through the bits in the current array index starting at 0
	for (i=0;i<8;i++)
	{
		crc <<= 1;
		if ((((data & 0x80)^(crc & 0x80)) != 0))
		{
                  crc ^= 0x09;
		}
		data <<= 1;
	}   // End Inner for loop
  }// End outer for loop

  crc = (crc<<1) | 1;

return(crc);

}


/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
uint8_t sd_spi_read_R1( void )
{
    uint8_t buffer_to_read;
    uint8_t dummy = 0xFF,i=0;


    //do{

		// read the R response
    sd_spi_transmit_receive(&dummy, &buffer_to_read, 1);
    sd_spi_transmit_receive(&dummy, &buffer_to_read, 1);
    //sd_spi_transmit_receive(&dummy, &buffer_to_read, 1);

    //sd_spi_transmit_receive(&dummy, &buffer_to_read, 1);
	//	sd_spi_transmit_receive(&dummy, &buffer_to_read, 1);
    //}while(i++ < 127 && (buffer_to_read == 0xFF));

    // return the response
    return buffer_to_read;

}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
uint8_t sd_spi_read_R7_or_R3( uint8_t *responseR7 )
{
    uint8_t responseR1;
    uint8_t responseDummy[4], i;

    for( i = 0 ; i < 4 ; i++ ){

    	responseDummy[i] = 0xFF;
    }


    responseR1 = sd_spi_read_R1();

    // read the R7 response
    sd_spi_transmit_receive(responseDummy, responseR7, 4);
    // return the R1 response
    return responseR1;

}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_send_acmd( uint8_t command, uint32_t argument )
{
    //send the command cmd 55 to indicate this is acmd
	sd_spi_send_cmd( 55, 0x00000000 );

    sd_spi_read_R1();

    // send the command
	sd_spi_send_cmd( command, argument );
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_send_data_packet(uint32_t data_token , uint16_t length , const uint8_t *data)
{

	uint16_t i;
	uint8_t tab[512] = {0xFF};
    //uint16_t crc;

	//data_token
    //buffer[0] = 0xFF;
	buffer[0] = data_token;

    //send data
    for(i=0; i<length ; i++){
        buffer[i+1] = data[i];
    }

    //calcul sur crc16
    //crc = sd_driver_cc2541_makeCRC16(buffer , length + 2);       crc is not used here to gain time

    //add crc16
    buffer[length+1] = 0;//(uint8_t)(crc >> 8);
    buffer[length+2] = 0;//(uint8_t)(crc);

	// write the commande on SPI
	//spi_driver_cc2541_write(length+3,buffer);
	sd_spi_transmit_receive( buffer, tab, length+3);
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_read_data_packet(uint32_t data_token , uint16_t length , uint8_t *data)
{
	uint16_t i;



    for(i=0; i<(length+2) ; i++){
        buffer[i] = 0xFF;
    }
    buffer[0] = data_token;
    buffer[length+1] = 0;// CRC
    buffer[length+2] = 0;// CRC
    //spi_driver_cc2541_read(512, data);
    sd_spi_transmit_receive(buffer, buffer, 515);

    for(i=0; i<length ; i++){
    	data[i] = buffer[i+1];
    }
}

/** \fn void
 * \param[in]
 * \param[out]
 * \author T.Folin
 * \test
 * \brief
 * \deprecated
 *            SLD_
 */
void sd_spi_send_stop( void ){
	uint8_t tab[1], resp[1];

	tab[0] = 0b11111101; // STOP_DATA_TOKEN_CMD25
	resp[0] = 0xFF;

	sd_spi_transmit_receive(tab, resp, 1);
}
