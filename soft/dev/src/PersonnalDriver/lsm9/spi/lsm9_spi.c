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

SPI_HandleTypeDef hspi2;


void lsm9_spi_init(){
	GPIO_InitTypeDef GPIO_InitStruct;
/*
	__GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	*/
	/* Initialisation du spi*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;  // clock < 10MHz
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLED;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspi2.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi2);



	/* PIN CS M */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_LSM_M;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_LSM_M, &GPIO_InitStruct);

	/* PIN CS X */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_LSM_X;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_LSM_X, &GPIO_InitStruct);

	/* PIN CS G */
	GPIO_InitStruct.Pin = GPIO_PIN_CS_LSM_G;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_CS_LSM_G, &GPIO_InitStruct);



}

ERROR_status lsm9_spi_transmit_receive_G(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_G, GPIO_PIN_CS_LSM_G, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive(&hspi2, pTxData, pRxData, Size, 0xFFFF);
	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_G, GPIO_PIN_CS_LSM_G, GPIO_PIN_SET );
	return ERROR_status_NOERROR;
}

ERROR_status lsm9_spi_transmit_receive_X(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_X, GPIO_PIN_CS_LSM_X, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive(&hspi2, pTxData, pRxData, Size, 0xFFFF);
	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_X, GPIO_PIN_CS_LSM_X, GPIO_PIN_SET );
	return ERROR_status_NOERROR;
}

ERROR_status lsm9_spi_transmit_receive_M(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size){

	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_M, GPIO_PIN_CS_LSM_M, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive(&hspi2, pTxData, pRxData, Size, 0xFFFF);
	HAL_GPIO_WritePin(GPIO_BLOCK_CS_LSM_M, GPIO_PIN_CS_LSM_M, GPIO_PIN_SET );

	return ERROR_status_NOERROR;
}
