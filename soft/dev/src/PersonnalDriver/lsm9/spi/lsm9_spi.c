/*
 *  Théo Folin
 *  2016
 * 	lsm9_spi.c
 *
 * A REFAIRE
 *
 *
 * */

#include "lsm9_spi.h"

SPI_HandleTypeDef hspi1;


void lsm9_spi_init(){
	GPIO_InitTypeDef GPIO_InitStruct;
/*
	__GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	*/
	/* Initialisation du spi*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;  // clock < 10MHz
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi1.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi1);



	/* PIN CS XM */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_LSM_M;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_LSM_M, &GPIO_InitStruct);


	/* PIN CS G */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_LSM_AG;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_LSM_AG, &GPIO_InitStruct);



}

ERROR_status lsm9_spi_transmit_receive_XG(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_AG, GPIO_PIN_CS_LSM_AG, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, Size, 0xFFFF);
	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_AG, GPIO_PIN_CS_LSM_AG, GPIO_PIN_SET );
	return ERROR_status_NOERROR;
}

ERROR_status lsm9_spi_transmit_receive_M(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_M, GPIO_PIN_CS_LSM_M, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, Size, 0xFFFF);
	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_M, GPIO_PIN_CS_LSM_M, GPIO_PIN_SET );

	return ERROR_status_NOERROR;
}
