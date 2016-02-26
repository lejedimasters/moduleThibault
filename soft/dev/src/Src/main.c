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


#define 	IHM_MODE		0
#define 	SENSOR_MODE		1

#if (IHM_MODE & SENSOR_MODE)
	#error soit IHM_MODE soit SENSOR_MODE
#endif

int main(void)
{

	/* MCU Configuration----------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	SystemClock_Config();







#if IHM_MODE

	seq_init();
#elif SENSOR_MODE

	lsm9_driver_init();
	uart_init();
#else
	#error definir mode de fonctionnement du module
#endif

	TIM4_init();





	while (1)

	{

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
	lsm9_data_typedef data;
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


#if SENSOR_MODE

	lsm9_driver_get_data(&data);
	printf("MAG X = ;%d; Y = ;%d; Z = ;%d;",data.magnotemeter.X,data.magnotemeter.Y,data.magnotemeter.Z);
	printf("ACC X = ;%d; Y = ;%d; Z = ;%d\r\n",data.accelerometry.X,data.accelerometry.Y,data.accelerometry.Z);
#else if IHM_MODE

	seq();
#endif

        }
    }
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
