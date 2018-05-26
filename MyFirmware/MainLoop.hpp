#pragma once
#include "MyIncludes.hpp"

uint16_t potReadings[3];
uint16_t duties[3];
float_t ThetaAngles[NUM_HINGES_IN_LEG];
Vector3D dest = Vector3D(150, 0, 0);
Vector3D minBoundaries = Vector3D(0, -150, -150);
Vector3D maxBoundaries = Vector3D(200, 150, 150);
Vector3D vvv;
RobotLeg rl;
uint8_t stage = 0;


int MainLoop() {

#pragma region ###_HereStartPeripherals_###
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
	rl = MyRobot.FrontRightLeg;
	stage = 0;




	while (1) {
		tick = HAL_GetTick();

		//Update status
		if (FrontLeftLeg.IsMoving())
			FrontLeftLeg.ContinueMove();
		if (FrontRightLeg.IsMoving())
			FrontRightLeg.ContinueMove();
		if (FrontLeftLeg.IsMoving())
			FrontLeftLeg.ContinueMove();
		if (FrontLeftLeg.IsMoving())
			FrontLeftLeg.ContinueMove();


		switch (stage)
		{
		case 0:
			stage = 1;
			break;
		case 1:
			stage += MyRobot.MoveOneLeg(FrontLeftLeg, Vector3D(0, 30, 0));
			break;
		case 2:
			stage += MyRobot.MoveOneLeg(FrontRightLeg, Vector3D(0, 30, 0));
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}











		//dest = rl.CurrentFootPosition.Add(Vector3D(-20, -20, 0));
		//if (!rl.IsMoving)
		//	rl.MoveByVector(Vector3D(10, 10, 0));
		//else
		//	rl.ContinueMove();

		//manual test inverse kinematic with potentiometers
		dest.X = mapToFloat_t(potReadings[0], 0, ADC_RESOLUTION, minBoundaries.X, maxBoundaries.X);
		dest.Y = mapToFloat_t(potReadings[1], 0, ADC_RESOLUTION, minBoundaries.Y, maxBoundaries.Y);
		dest.Z = mapToFloat_t(potReadings[2], 0, ADC_RESOLUTION, minBoundaries.Z, maxBoundaries.Z);

		////go by vector and back in loop
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

		for (int i = 0; i < NUM_HINGES_IN_LEG; i++) {
			ThetaAngles[i] = MyRobot.FrontLeftLeg.Servos[i].theta;
		}

		dest.X = 200;
		rl.SetPosition(dest);
		//HAL_Delay(500);
		dest.X = 150;

		for (int i = 0; i < NUM_HINGES_IN_LEG; i++) {
			rl.Servos[i].SetCCRValueByAngle_DEG(mapToFloat_t(potReadings[i], 0, ADC_RESOLUTION, -120, 120));
		}

		//ss.SetCCRbyAngle(90);
		HAL_Delay(delay);

		//manual test straight kinematic, servos ccr boundaries etc
		rl.Servos[0].SetCCRValueByAngle_DEG(testAngles.X);
		rl.Servos[1].SetCCRValueByAngle_DEG(testAngles.Y);
		rl.Servos[2].SetCCRValueByAngle_DEG(testAngles.Z);

		/*
		//HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)&duties[0], 1);
		//HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t*)&duties+4, 1);
		//HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t*)&duties+8, 1);
		//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		//HAL_Delay(100);
		//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		//HAL_Delay(100);
		*/
	}
};


