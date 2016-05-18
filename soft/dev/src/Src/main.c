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
#include "sd_driver.h"
#include "board.h"
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

#define 	TIME_BASE_MS	10


#if (NUCLEO_BOARD & THsBOARD )
	#error soit NUCLEO_BOARD soit THsBOARD
#endif






FATFS fs;


/*
* DRDY_M		cpt  --> µc
* INT_M		cpt  --> µc
* INT1_A/G		cpt  --> µc
* INT2_A/G		cpt  --> µc
* DEN_A/G		cpt  <-- µc
* */
void debug_carte(){
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_DRDY_M;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_DRDY_M, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_INT_M;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_INT_M, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_INT1_AG;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_INT1_AG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_INT2_AG;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_INT2_AG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_DEN_AG;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIO_BLOCK_DEN_AG, &GPIO_InitStruct);


}



int main(void)
{

	FRESULT res;

	/* MCU Configuration----------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	SystemClock_Config();
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();


	#if THsBOARD

/*
		sd_driver_init();
		res = FR_DISK_ERR;
		   while( res != FR_OK){
		        res = pf_mount(&fs);
		   }

		   // find the file TEST.txt
		   res = FR_DISK_ERR;
		   while( res != FR_OK){
		        res = pf_open("TEST.txt");
		    }*/
		lsm9_driver_init();
		uart_init();
		debug_carte();
		TIM4_init();



	#elif	NUCLEO_BOARD
		seq_init(10);
		TIM4_init();


	#endif






	while (1){
		//__WFI();
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


void TIM4_init(void){
	  __TIM4_CLK_ENABLE();
	  /* prescaler 5  Period = 26785; -> 10ms*/
	  TIM_Handle.Init.Prescaler = 1000;
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
#if THsBOARD
	lsm9_data_typedef data;
	static uint32_t time = 0x0;
#endif


	//HAL_StatusTypeDef status;
    if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
    {
        if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
            /*put your code here */


			#if THsBOARD
				/*
				data.gyroscope.X = 4444;
				data.accelerometry.X = 1111;
				data.magnotemeter.X = 7777;

				data.gyroscope.Y = 5555;
				data.accelerometry.Y = 2222;
				data.magnotemeter.Y = 8888;

				data.gyroscope.Z = 6666;
				data.accelerometry.Z = 3333;
				data.magnotemeter.Z = 9999;

				lsm9_driver_get_data(&data);
				sd_driver_fill_buffer(&data,time);
				time += 491;
				sd_driver_bufferswitcher_emptying();*/


				lsm9_driver_init();
			#elif	NUCLEO_BOARD
				seq();

			#endif

        }
    }
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
