/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sequencer.h"
#include "driver_led.h"
#include "stdio.h"
#include "lsm9_driver.h"
/*
 *
 * */


/*
 *
 * */

//void MX_SPI1_Init(void);
void SystemClock_Config(void);
void TIM4_IRQHandler(void);
void TIM4_init(void);



TIM_HandleTypeDef TIM_Handle;





int main(void)
{
//	uint8_t RX_tab[9]={'\0'};
//	uint8_t writeTab[9] ={0,0,0,0,0,0,0,0,0};
//	uint8_t readTab[9] ={0,0,0,0,0,0,0,0,0};
	/* MCU Configuration----------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	SystemClock_Config();



//	seq_init();


	uart_init();
	//MX_SPI1_Init();
	//driver_led_init();


	lsm9_driver_init();
/*
		// CTRL_REG0_XM     rboot memory content
		writeTab[0] = SPI_WRITE | NO_INC | 0x1F;
		writeTab[1] = 0b10000000;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
		HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 2, 0xFFFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );



		// CTRL_REG1_XM    100Hz, enable all axis   output registers not updated until MSB and LSB have been		read
	  writeTab[0] = SPI_WRITE | NO_INC | 0x20;
	  writeTab[1] = 0b00011111;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
	  HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 2, 0xFFFF);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );

		// CTRL_REG5_XM    temperature enable, low res mag, defaut odr mag
	  writeTab[0] = SPI_WRITE | NO_INC | 0x24;
	  writeTab[1] = 0b10011000;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
	  HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 2, 0xFFFF);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );
*/
	  TIM4_init();

	while (1)

	{
/*
		while( uart_receive(RX_tab, 1) != HAL_OK);
		if( RX_tab[0] == 0x03 ){

			driver_led_toggle();
			printf("USART1 Stream\n");
		}
*/
	}
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}





/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
	NOP();
}

#endif
//
//void MX_SPI1_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//
//	__GPIOA_CLK_ENABLE();
//	__GPIOB_CLK_ENABLE();
//
//  hspi1.Instance = SPI1;
//  hspi1.Init.Mode = SPI_MODE_MASTER;
//  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
//  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
//  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
//  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
//  hspi1.Init.NSS = SPI_NSS_SOFT;
//  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
//  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
//  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
//  hspi1.Init.CRCPolynomial = 10;
//  HAL_SPI_Init(&hspi1);
//
//  GPIO_InitStruct.Pin = GPIO_PIN_6;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//}

void TIM4_init(void){
	  __TIM4_CLK_ENABLE();
	  /* prescaler 5  Period = 26785; -> 10ms*/
	  TIM_Handle.Init.Prescaler = 500;
	  TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	  TIM_Handle.Init.Period = 26785;
	  TIM_Handle.Instance = TIM4;   //Same timer whose clocks we enabled
	  HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
	  HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
	  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	  HAL_NVIC_EnableIRQ(TIM4_IRQn);
}



void TIM4_IRQHandler(void)
{
	acc_data_typedef data;
	/*
	uint8_t readTab[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t writeTab[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int16_t acc_X_hight, acc_Y_hight, acc_Z_hight, temp_hight;
	int16_t acc_X_low, acc_Y_low, acc_Z_low, temp_low;
	int16_t acc_X, acc_Y, acc_Z, temp;*/

	HAL_StatusTypeDef status;
    if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
    {
        if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
            /*put your code here */



		#if SCHEDULER_ON
			  SCHEDULER();
		#else
/*
			  writeTab[0] = SPI_READ | NO_INC | REG_WHOAMI_ADDR;
//driver_led_toggle();

			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
			  status = HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 2, 0xFFFF);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );



			  status = status;
			  writeTab[0] = SPI_READ | INC | 0x28;
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
			  status = HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 7, 0xFFFF);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );

				acc_X_low  = readTab[1];
				acc_X_hight = readTab[2];
				acc_Y_low = readTab[3];
				acc_Y_hight  = readTab[4];
				acc_Z_low = readTab[5];
				acc_Z_hight  = readTab[6];

			  writeTab[0] = SPI_READ | INC | 0x05;
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET );
			  status = HAL_SPI_TransmitReceive(&hspi1, writeTab, readTab, 3, 0xFFFF);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET );
			  temp_low = readTab[2];
			  temp_hight = readTab[1];
			 // uart_send(writeTab, 3);



			  printf("X = %x %x, Y = %x %x, Z = %x %x, temp = %d\r\n",acc_X_hight,acc_X_low,acc_Y_hight,acc_Y_low, acc_Z_hight, acc_Z_low, temp);
			  acc_X = (acc_X_hight)*256 + acc_X_low;
			  acc_Y = (acc_Y_hight)*256 + acc_Y_low;
			  acc_Z = (acc_Z_hight)*256 + acc_Z_low;
			  temp = (temp_hight)*256 + temp_low;
			  printf("X = %d, Y = %d, Z = %d, temp = %d\r\n",acc_X,acc_Y,acc_Z, temp);



			  status = status;
	  //SCHEDULER();
	    */

			  lsm9_driver_get_accelerometry(&data);
			 printf("X = %d, Y = %d, Z = %d\r\n",data.X,data.Y,data.Z);
		#endif
            //seq();
        }
    }
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
