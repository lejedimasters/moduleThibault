/*
 *  Théo Folin
 *  2016
 * 	uart.c
 *
 * A REFAIRE
 *
 *
 * */


#include "uart.h"






static UART_HandleTypeDef huart2;

/* USART2 init function */
void uart_init(void)
{
	__GPIOA_CLK_ENABLE();
//	__USART2_CLK_ENABLE();


	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);

}



void uart_send( int8_t *tab, uint16_t size ){
	HAL_UART_Transmit(&huart2,(uint8_t *)tab,size,0xFFFF);
}

uint32_t uart_receive( uint8_t *tab, uint16_t size ){
	uint32_t ret;

	ret = HAL_UART_Receive(&huart2, tab, size, 0xFFFF);

	return ret;
}
