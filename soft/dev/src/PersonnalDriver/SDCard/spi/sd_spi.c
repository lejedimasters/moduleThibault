/*
 *  Th�o Folin
 *  2016
 * 	sd_spi.c
 *
 * A REFAIRE
 *
 *
 * */

#include "sd_spi.h"

SPI_HandleTypeDef hspi3;

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

	HAL_SPI_MspDeInit(&hspi3);

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
	hspi3.Instance = SPI1;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;

	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;

//	hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
//	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;

//	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
//	hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;

//	hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
//	hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;

	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; 	// 84MHz/ 256
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi3.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi3);


	/* PIN CS SD */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_SDCARD;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_SDCARD, &GPIO_InitStruct);
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

	__GPIOC_CLK_ENABLE();
	/* Initialisation du spi*/
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; 	// 84MHz / 2
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi3.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi3);


	/* PIN CS XM */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_SDCARD;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_SDCARD, &GPIO_InitStruct);
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
	HAL_SPI_TransmitReceive(&hspi3, pTxData, pRxData, Size, 0xFFFF);
	sd_spi_cs_up();
	return ERROR_status_NOERROR;
}

ERROR_status dummyclock();
ERROR_status dummyclock(){
	uint8_t tab[80] = {0x00},i;

	for( i = 0 ; i < 80 ; i++ ){

		tab[i] = 0xFF;
	}


	HAL_SPI_TransmitReceive(&hspi3, tab, tab, 80, 0xFFFF);
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

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_SDCARD, GPIO_PIN_CS_SDCARD, GPIO_PIN_RESET );
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

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_SDCARD, GPIO_PIN_CS_SDCARD, GPIO_PIN_SET );
}
