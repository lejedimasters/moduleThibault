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



ERROR_status uart_send_data_bytes( lsm9_data_typedef *data){
	int8_t data_tab[9*2+4];
	int8_t *p;
	uint8_t i;


	p = (int8_t *)data;

/*
	for( i = 0 ; i < (9*2+4) ; i++ ){
		data_tab[i] = p[i];
	}
*/
	data_tab[0]=(int8_t)((data->magnotemeter.X)>>8);
	data_tab[1]=(int8_t)((data->magnotemeter.X)>>0);
	data_tab[2]=(int8_t)((data->magnotemeter.Y)>>8);
	data_tab[3]=(int8_t)((data->magnotemeter.Y)>>0);
	data_tab[4]=(int8_t)((data->magnotemeter.Z)>>8);
	data_tab[5]=(int8_t)((data->magnotemeter.Z)>>0);
	data_tab[6]=(int8_t)((data->accelerometry.X)>>8);
	data_tab[7]=(int8_t)((data->accelerometry.X)>>0);
	data_tab[8]=(int8_t)((data->accelerometry.Y)>>8);
	data_tab[9]=(int8_t)((data->accelerometry.Y)>>0);
	data_tab[10]=(int8_t)((data->accelerometry.Z)>>8);
	data_tab[11]=(int8_t)((data->accelerometry.Z)>>0);
	data_tab[12]=(int8_t)((data->gyroscope.X)>>8);
	data_tab[13]=(int8_t)((data->gyroscope.X)>>0);
	data_tab[14]=(int8_t)((data->gyroscope.Y)>>8);
	data_tab[15]=(int8_t)((data->gyroscope.Y)>>0);
	data_tab[16]=(int8_t)((data->gyroscope.Z)>>8);
	data_tab[17]=(int8_t)((data->gyroscope.Z)>>0);
	data_tab[18]=(int8_t)((data->time_ms)>>24);
	data_tab[19]=(int8_t)((data->time_ms)>>16);
	data_tab[20]=(int8_t)((data->time_ms)>>8);
	data_tab[21]=(int8_t)((data->time_ms)>>0);





	/*
	data->magnotemeter.X 	2
	data->magnotemeter.Y	4
	data->magnotemeter.Z	6
	data->accelerometry.X	8
	data->accelerometry.Y	10
	data->accelerometry.Z	12
	data->gyroscope.X		14
	data->gyroscope.Y		16
	data->gyroscope.Z		18
	data->time_ms			22
*/
	uart_send(data_tab, (9*2+4));
	return ERROR_status_NOERROR;
}

ERROR_status uart_send_data_ASCII( lsm9_data_typedef *data){

	printf("MAG X = ;%d; Y = ;%d; Z = ;%d;",data->magnotemeter.X,data->magnotemeter.Y,data->magnotemeter.Z);
	printf("ACC X = ;%d; Y = ;%d; Z = ;%d\r\n",data->accelerometry.X,data->accelerometry.Y,data->accelerometry.Z);
	printf("GYR X = ;%d; Y = ;%d; Z = ;%d\r\n",data->gyroscope.X,data->gyroscope.Y,data->gyroscope.Z);

	return ERROR_status_NOERROR;
}

