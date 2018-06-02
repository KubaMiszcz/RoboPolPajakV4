#pragma once
#include "MyIncludes.hpp"

uint16_t potReadings[3];
uint16_t duties[3];
float_t ThetaAngles[NUM_HINGES_IN_LEG];
Vector3D dest = Vector3D(150, 0, 0);
Vector3D minBoundaries = Vector3D(0, -150, -150);
Vector3D maxBoundaries = Vector3D(200, 150, 150);
Vector3D vvv;
RobotLeg* rl;
uint8_t stage = 0;

/// ********************************************************************************
/// <summary>
/// Main Loop moves here for convenience from CubeMX
/// </summary>
/// <created>KubaMiszcz,2018-05-25</created>
/// <changed>KubaMiszcz,2018-05-25</changed>
inline int MainLoop() {

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
	uint16_t delay = 1;
	int32_t a = 3000;
	mapToFloat_t(65, 83, 45, 6400, 5075);
	Vector3D testAngles = Vector3D(150, 0, 0);
	dest = Vector3D(100, 100, -75);
	minBoundaries = Vector3D(0, -150, -150);
	maxBoundaries = Vector3D(200, 150, 150);
	RobotLeg FrontLeftLeg = MyRobot.AllLegs[e_FrontLeftLeg];
	RobotLeg FrontRightLeg = MyRobot.AllLegs[e_FrontRightLeg];
	RobotLeg RearRightLeg = MyRobot.AllLegs[e_RearRightLeg];
	RobotLeg RearLeftLeg = MyRobot.AllLegs[e_RearLeftLeg];
	rl = &MyRobot.AllLegs[e_FrontRightLeg];
	stage = 0;
	(*rl).SetPosition(Vector3D(200, 50, -75));
	(*rl).MoveToPoint(Vector3D(0, 200, -75));
	uint8_t dir = 1;

	while (true) {
		tick = HAL_GetTick();

		//Update status
		//if (MyRobot.AllLegs[e_FrontLeftLeg].IsMoving())
		//	MyRobot.AllLegs[e_FrontLeftLeg].ContinueMove();
		if (MyRobot.AllLegs[e_FrontRightLeg].IsMoving())
			MyRobot.AllLegs[e_FrontRightLeg].ContinueMove();
		//if (MyRobot.AllLegs[e_RearRightLeg].IsMoving())
		//	MyRobot.AllLegs[e_RearRightLeg].ContinueMove();
		//if (MyRobot.AllLegs[e_RearLeftLeg].IsMoving())
		//	MyRobot.AllLegs[e_RearLeftLeg].ContinueMove();

		if (!MyRobot.AllLegs[e_FrontRightLeg].IsMoving() && dir == 1) {
			dir = 2;
			(*rl).MoveToPoint(Vector3D(200, 50, -75));
		}
		if (!MyRobot.AllLegs[e_FrontRightLeg].IsMoving() && dir == 2) {
			dir = 1;
			(*rl).MoveToPoint(Vector3D(0, 200, -75));
		}




		//switch (stage)
		//{
		//case 0:
		//	stage = 1;
		//	break;
		//case 1:
		//	//it returns 1 when done, then adds to stage, otherwise 0
		//	stage += MyRobot.MoveOneLeg(MyRobot.AllLegs[e_FrontLeftLeg], Vector3D(0, 30, 0));
		//	break;
		//case 2:
		//	stage += MyRobot.MoveOneLeg(MyRobot.AllLegs[e_FrontRightLeg], Vector3D(0, 30, 0));
		//	break;
		//case 3:
		//	break;
		//case 4:
		//	break;
		//case 5:
		//	break;
		//default:
		//	break;
		//}











		//dest = rl.CurrentFootPosition.Add(Vector3D(-20, -20, 0));
		//if (!rl.IsMoving)
		//	rl.MoveByVector(Vector3D(10, 10, 0));
		//else
		//	rl.ContinueMove();

		//manual test inverse kinematic with potentiometers
		//dest.X = mapToFloat_t(potReadings[0], 0, ADC_RESOLUTION, minBoundaries.X, maxBoundaries.X);
		//dest.Y = mapToFloat_t(potReadings[1], 0, ADC_RESOLUTION, minBoundaries.Y, maxBoundaries.Y);
		//dest.Z = mapToFloat_t(potReadings[2], 0, ADC_RESOLUTION, minBoundaries.Z, maxBoundaries.Z);

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

		//for (size_t i = 0; i < NUM_HINGES_IN_LEG; i++) {
		//	ThetaAngles[i] = MyRobot.FrontLeftLeg.Servos[i].theta;
		//}

		//dest.X = 200;
		//rl.SetPosition(dest);
		////HAL_Delay(500);
		//dest.X = 150;

		//for (int i = 0; i < NUM_HINGES_IN_LEG; i++) {
		//	rl.Servos[i].SetCCRValueByAngle_DEG(mapToFloat_t(potReadings[i], 0, ADC_RESOLUTION, -120, 120));
		//}

		////ss.SetCCRbyAngle(90);
		//HAL_Delay(delay);

		////manual test straight kinematic, servos ccr boundaries etc
		//rl.Servos[0].SetCCRValueByAngle_DEG(testAngles.X);
		//rl.Servos[1].SetCCRValueByAngle_DEG(testAngles.Y);
		//rl.Servos[2].SetCCRValueByAngle_DEG(testAngles.Z);

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
}

