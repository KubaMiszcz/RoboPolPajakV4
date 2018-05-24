
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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "MyIncludes.hpp"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//!++Debug Only
uint16_t potReadings[3];
uint16_t duties[3];
float_t ThetaAngles[NUM_HINGES_IN_LEGS];
Vector3D dest = Vector3D(150, 0, 0);
Vector3D minBoundaries = Vector3D(0, -150, -150);
Vector3D maxBoundaries = Vector3D(200, 150, 150);
Vector3D vvv;
RobotLeg rl;
uint8_t stage = 0;

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
	MX_TIM3_Init();
	MX_I2C1_Init();
	/* USER CODE BEGIN 2 */

#pragma region HereStartPeripherals
	HAL_Delay(50);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)potReadings, 3);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
#pragma endregion

	//++generate Robot
	Robot MyRobot = Robot();
	MyRobot.InitMCUPeripherals();
	MyRobot.InitRobotProperties();

	//++generateLeg
	rl = MyRobot.FrontRightLeg;

	//++debug only variables
	uint16_t delay = 2;
	int32_t a = 3000;
	mapToFloat_t(65, 83, 45, 6400, 5075);
	Vector3D testAngles = Vector3D(150, 0, 0);
	dest = Vector3D(100, 100, -75);
	minBoundaries = Vector3D(0, -150, -150);
	maxBoundaries = Vector3D(200, 150, 150);
	vvv = rl.GetFootPosition();
	RobotLeg FrontLeftLeg = MyRobot.FrontLeftLeg;
	RobotLeg FrontRightLeg = MyRobot.FrontRightLeg;
	RobotLeg RearRightLeg = MyRobot.RearRightLeg;
	RobotLeg RearLeftLeg = MyRobot.RearLeftLeg;
	stage = 0;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		tick = HAL_GetTick();
		Vector3D wert;
		Vector3D v123 = Vector3D();
		Vector3D ff = v123 + v123;
		Vector3D aa = Vector3D(1, 1, 1) + Vector3D(2, 2, 2);
		Vector3D bb = aa + aa;
		Vector3D cc = aa.Negate();
		Vector3D dd = aa.Add(bb);
		Vector3D rr = aa;
		rr.Negate();
		float_t ee = Vector3D(1, 5, 6).AbsMaxCoord();









		//dest = rl.CurrentFootPosition.Add(Vector3D(-20, -20, 0));
		//if (!rl.IsMoving)
		//	rl.MoveByVector(Vector3D(10, 10, 0));
		//else
		//	rl.ContinueMove();

		////#################################
		////OneStepForward sequence
		////#################################
		//HAL_Delay(MyRobot.delay);

		//float_t moveCG = 20;
		//float_t moveUp = 30;
		//float_t moveDown = -moveUp;
		//float_t moveForward = 30;
		//Vector3D moveCGVector;
		////############################### START 1st FrontLeftLeg ###########################
		////simultaneously move CG slighly oppose to moving leg -> right back
		//moveCGVector = Vector3D(moveCG, -moveCG, 0).Negate();
		//stage = 1;
		//switch (stage)
		//{
		//case 1:
		//	FrontLeftLeg.MoveByVector(moveCGVector);
		//	FrontRightLeg.MoveByVector(moveCGVector);
		//	RearRightLeg.MoveByVector(moveCGVector);
		//	RearLeftLeg.MoveByVector(moveCGVector);
		//	stage++;
		//	break;
		//case 2:
		//	if (!MyRobot.IsMoving())
		//		stage++;
		//	break;
		//case 3:
		//	//start lift up leg, move formawr, lift down
		//	FrontLeftLeg.MoveByVector(0, 0, moveUp);
		//	if (!FrontLeftLeg.IsMoving)
		//		stage++;
		//	break;
		//case 4:
		//	FrontLeftLeg.MoveByVector(0, moveForward, 0);
		//	if (!FrontLeftLeg.IsMoving)
		//		stage++;
		//	break;
		//case 5:
		//	FrontLeftLeg.MoveByVector(0, 0, moveDown);
		//	if (!FrontLeftLeg.IsMoving)
		//		stage++;
		//	break;
		//default:
		//	break;
		//}

		////Update status
		//if (FrontLeftLeg.IsMoving)
		//	FrontLeftLeg.ContinueMove();
		//if (FrontRightLeg.IsMoving)
		//	FrontRightLeg.ContinueMove();
		//if (FrontLeftLeg.IsMoving)
		//	FrontLeftLeg.ContinueMove();
		//if (FrontLeftLeg.IsMoving)
		//	FrontLeftLeg.ContinueMove();

		////######################### END 1ST FrontLeftLeg ########################################

		////######################## START 2nd FrontRightLeg ###################################
		////move CG slighly oppose to moving leg -> left
		//moveCGVector = Vector3D(-moveCG, moveCG, 0).Add(-moveCG, -moveCG, 0).Negate();
		//FrontLeftLeg.MoveByVector(moveCGVector);
		//FrontRightLeg.MoveByVector(moveCGVector);
		//RearRightLeg.MoveByVector(moveCGVector);
		//RearLeftLeg.MoveByVector(moveCGVector);
		////lift up leg, move formawr, lift down
		//FrontRightLeg.MoveByVector(0, 0, moveUp);
		//FrontRightLeg.MoveByVector(0, moveForward, 0);
		//FrontRightLeg.MoveByVector(0, 0, moveDown);
		////######################### END 2nd FrontRightLeg ########################################

		////######################## START 3nd RearRightLeg ###################################
		////move CG slighly oppose to moving leg -> left
		//moveCGVector = Vector3D(moveCG, moveCG, 0).Add(-moveCG, moveCG, 0).Negate();
		//FrontLeftLeg.MoveByVector(moveCGVector);
		//FrontRightLeg.MoveByVector(moveCGVector);
		//RearRightLeg.MoveByVector(moveCGVector);
		//RearLeftLeg.MoveByVector(moveCGVector);
		////lift up leg, move formawr, lift down
		//RearRightLeg.MoveByVector(0, 0, moveUp);
		//RearRightLeg.MoveByVector(0, moveForward, 0);
		//RearRightLeg.MoveByVector(0, 0, moveDown);
		////######################### END 3nd RearRightLeg ########################################

		////######################## START 4nd RearLeftLeg ###################################
		////move CG slighly oppose to moving leg -> left
		//moveCGVector = Vector3D(moveCG, -moveCG, 0).Add(moveCG, moveCG, 0).Negate();
		//FrontLeftLeg.MoveByVector(moveCGVector);
		//FrontRightLeg.MoveByVector(moveCGVector);
		//RearRightLeg.MoveByVector(moveCGVector);
		//RearLeftLeg.MoveByVector(moveCGVector);
		////lift up leg, move formawr, lift down
		//RearLeftLeg.MoveByVector(0, 0, moveUp);
		//RearLeftLeg.MoveByVector(0, moveForward, 0);
		//RearLeftLeg.MoveByVector(0, 0, moveDown);
		////######################### END 4nd RearLeftLeg ########################################

		//// ##################### START Pose stand Up #########################
		//moveUp = 100;
		//moveDown = -moveUp;
		//moveCGVector = Vector3D(0, 0, moveUp).Negate();
		//FrontLeftLeg.MoveByVector(moveCGVector);
		//FrontRightLeg.MoveByVector(moveCGVector);
		//RearRightLeg.MoveByVector(moveCGVector);
		//RearLeftLeg.MoveByVector(moveCGVector);
		//// ##################### END Pose stand Up #########################

		// ##################### START Pose lay down #########################
		// cos jka kroki tylko nogi wszerz ale musi tuptac i chyba ten srodek ciezkosci balansowac
		// jak dopracuej kroki to wteyd to
		// ##################### END Pose lay down #########################

		///manual test inverse kinematic with potentiometers
		//dest.X = mapToFloat_t(potReadings[0], 0, ADC_RESOLUTION, minBoundaries.X, maxBoundaries.X);
		//dest.Y = mapToFloat_t(potReadings[1], 0, ADC_RESOLUTION, minBoundaries.Y, maxBoundaries.Y);
		//dest.Z = mapToFloat_t(potReadings[2], 0, ADC_RESOLUTION, minBoundaries.Z, maxBoundaries.Z);

		///go by vector and back in loop
		// for (size_t i = 0; i < 1500; i++)
		// {
		// 	dest.Add(Vector3D(-0.1, 0.1, 0));
		// 	rl.SetPosition(dest);
		// 	HAL_Delay(delay);
		// }

		// for (size_t i = 0; i < 1500; i++)
		// {
		// 	dest.Add(Vector3D(0.1, -0.1, 0));
		// 	rl.SetPosition(dest);
		// 	HAL_Delay(delay);
		// }

		//for (int i = 0; i < NUM_HINGES_IN_LEGS; i++) {
		//	ThetaAngles[i] = MyRobot.FrontLeftLeg.Servos[i].theta;
		//}

		//dest.X = 200;
		//rl.SetPosition(dest);
		//HAL_Delay(500);
		//dest.X = 150;

		//for (int i = 0; i < NUM_HINGES_IN_LEGS; i++) {
		//	rl.Servos[i].SetCCRValueByAngle_DEG(mapToLong(potReadings[i], 0, ADC_RESOLUTION, -120, 120));
		//}

		//ss.SetCCRbyAngle(90);
		//HAL_Delay(delay);

		///manual test straight kinematic, servos ccr boundaries etc
		//rl.Servos[0]->SetCCRValueByAngle_DEG(testAngles.X);
		//rl.Servos[1]->SetCCRValueByAngle_DEG(testAngles.Y);
		//rl.Servos[2]->SetCCRValueByAngle_DEG(testAngles.Z);

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
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
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
