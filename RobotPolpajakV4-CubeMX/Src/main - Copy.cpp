
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "MyIncludes.hpp"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//#################################################################################
//####################  Private variables    ######################################
//#################################################################################
//static const uint16_t minCCR = 0;
//static const uint16_t maxCCR = 10000;
uint16_t potReadings[3];
uint16_t duties[3];

//!++Debug Only
float_t ThetaAngles[NUM_HINGES_IN_LEGS];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
		//HAL_Delay(50);
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_TIM1_Init();
	MX_ADC1_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)potReadings, 3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);


	//debug only variables
	uint16_t 	delay = 500;
	int32_t a = 3000;
	Vector3D vvv;
	//HAL_Delay(50);
	mapToFloat(65, 83, 45, 6400, 5075);

	//generateLeg
	//RobotLeg(Vector3D offsetFromRobotOrigin,float lengths[NUM_HINGES_IN_LEGS], Servo* servos[NUM_HINGES_IN_LEGS])

	Vector3D offsetFromOrigin;
	offsetFromOrigin = Vector3D(0, 0, 0);

	uint16_t lengths[NUM_HINGES_IN_LEGS] = { 32,65,106 };

	uint16_t characteristicCCRs1[5] = { 7894,5930,4550,3340,2094 };
	Servo servo1 = Servo(&htim1.Instance->CCR1, characteristicCCRs1);

	uint16_t characteristicCCRs2[5] = { 6600,5125,3850,2750,1650 };
	Servo servo2 = Servo(&htim1.Instance->CCR2, characteristicCCRs2);

	uint16_t characteristicCCRs3[5] = { 1678,2825,3975,5325,7121 };
	Servo servo3 = Servo(&htim1.Instance->CCR3, characteristicCCRs3);

	Servo servos[NUM_HINGES_IN_LEGS] = { servo1, servo2, servo3 };

	RobotLeg rl = RobotLeg(offsetFromOrigin, lengths, servos);
	vvv = rl.GetFootPosition();

	//Servo ss = Servo(&TIM1->CCR1);
	//ss.degPos90CCR = 6600;
	//ss.degPos45CCR = 5125;
	//ss.deg0CCR = 3850;
	//ss.degNeg45CCR = 2750;
	//ss.degNeg90CCR = 1650;

	//Robot MyRobot = Robot();
	//MyRobot.InitMCUPeripherals();
	//MyRobot.InitProgramProperties();
	//MyRobot.InitConstructionProperties();
	//MyRobot.InitConstructionProperties();
	Vector3D testAngles = Vector3D(150, 0, 0);
	Vector3D dest = Vector3D(150, 0, 0);
	Vector3D minBoundaries = Vector3D(0, -150, -150);
	Vector3D maxBoundaries = Vector3D(200, 150, 150);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		tick = HAL_GetTick();

		///manual test inverse kinematic with potentiometers
		dest.X = mapToLong(potReadings[0], 0, ADC_RESOLUTION, minBoundaries.X, maxBoundaries.X);
		dest.Y = mapToLong(potReadings[1], 0, ADC_RESOLUTION, minBoundaries.Y, maxBoundaries.Y);
		dest.Z = mapToLong(potReadings[2], 0, ADC_RESOLUTION, minBoundaries.Z, maxBoundaries.Z);
		rl.SetPosition(dest);

		for (int i = 0; i < NUM_HINGES_IN_LEGS; i++) {
			ThetaAngles[i] = rl.Servos[i].theta;
		}

		
		//HAL_Delay(500);
		//dest.X = 200;
		//rl.SetPosition(dest);
		//HAL_Delay(500);
		//dest.X = 150;
		//for (int i = 0; i < NUM_HINGES_IN_LEGS; i++) {
		//	rl.Servos[i]->SetCCRValuebyAngle(mapToLong(potReadings[i], 0, ADC_RESOLUTION, -90, 90));
		//}


		//for (int i = 0; i < NUM_HINGES_IN_LEGS; i++) {
		//	rl.Servos[i]->SetCCRValuebyAngle(mapToLong(potReadings[i], 0, ADC_RESOLUTION, -90, 90));
		//}


		//ss.SetCCRbyAngle(90);
		//HAL_Delay(delay);


		///manual test straight kinematic, servos ccr boundaries etc
		//rl.Servos[0]->SetCCRValuebyAngle(testAngles.X);
		//rl.Servos[1]->SetCCRValuebyAngle(testAngles.Y);
		//rl.Servos[2]->SetCCRValuebyAngle(testAngles.Z);




		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/*
	 //HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)&duties[0], 1);
	 //HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t*)&duties+4, 1);
	 //HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t*)&duties+8, 1);
	 //HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	 //HAL_Delay(100);
	 //HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	 //HAL_Delay(100);
	 */
	 /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	*/
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
	/* USER CODE BEGIN Error_Handler_Debug */
		/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
		/* User can add his own implementation to report the file name and line number,
		 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
		 /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

  /**
	* @}
	*/

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
