#pragma once
#include "RobotLeg.hpp"
class Robot
{
public:
	Vector3D CurrentPosition;
	RobotLeg FrontLeftLeg;
	RobotLeg FrontRightLeg;
	RobotLeg RearLeftLeg;
	RobotLeg RearRightLeg;
	RobotLeg AllLegs[4];

	//=============
	uint16_t potReadings[3];
	uint16_t duties[3];

	//Robot() {};

	void InitMCUPeripherals() {
		

		//HAL_ADC_Start_DMA(&hadc1, (uint32_t*)potReadings, 3);

		//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

	};
	void InitRobotProperties() {
		//FrontLeftLeg = new RobotLeg();
	};

	void InitProgramProperties() {
		//FrontLeftLeg = new RobotLeg;
		//FrontLeftLeg->Servos[0]->ptrCCR = &htim1.Instance->CCR1;
		//FrontLeftLeg->Servos[1]->ptrCCR = &htim1.Instance->CCR2;
		//FrontLeftLeg->Servos[2]->ptrCCR = &htim1.Instance->CCR3;

		//FrontRightLeg = new RobotLeg;
		//FrontRightLeg->Servos[0]->ptrCCR = &htim2.Instance->CCR1;
		//FrontRightLeg->Servos[1]->ptrCCR = &htim2.Instance->CCR2;
		//FrontRightLeg->Servos[2]->ptrCCR = &htim2.Instance->CCR3;
		
		/*RearLeftLeg = new RobotLeg;		
		FrontRightLeg->Servos[0]->ptrCCR = &htim2.Instance->CCR1;
		FrontRightLeg->Servos[1]->ptrCCR = &htim2.Instance->CCR2;
		FrontRightLeg->Servos[2]->ptrCCR = &htim2.Instance->CCR3;*/

		/*RearRightLeg = new RobotLeg;
		FrontRightLeg->Servos[0]->ptrCCR = &htim2.Instance->CCR1;
		FrontRightLeg->Servos[1]->ptrCCR = &htim2.Instance->CCR2;
		FrontRightLeg->Servos[2]->ptrCCR = &htim2.Instance->CCR3;*/
		
	};

	void InitConstructionProperties() {
		float_t arr[3] = { 1,2,3 };
		FrontLeftLeg.Length[0] = 10;
		FrontLeftLeg.Length[1] = 50;
		FrontLeftLeg.Length[2] = 100;
		FrontLeftLeg.GetFootPosition();
	};

};



	//uint8_t Speed = 88;
	//uint8_t ui8 = 130;
	//int8_t i8=130;
	//uint16_t ui16 = 65000;
	//int16_t i16 = 65000;
