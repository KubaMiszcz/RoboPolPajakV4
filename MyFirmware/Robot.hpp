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

	Robot() {};

	void InitMCUPeripherals() {

	};
	void InitRobotProperties() {
#pragma region FrontLeftLeg
		Vector3D offsetFromOrigin = Vector3D(0, 0, 0);
		uint16_t lengths[NUM_HINGES_IN_LEGS] = { 32,65,106 };

		uint16_t characteristicCCRs1[5] = { 7894,5930,4550,3340,2094 };
		uint16_t characteristicCCRs2[5] = { 6600,5125,3850,2750,1650 };
		uint16_t characteristicCCRs3[5] = { 1678,2825,3975,5325,7121 };

		Servo servo1 = Servo(&htim1.Instance->CCR1, characteristicCCRs1);
		Servo servo2 = Servo(&htim1.Instance->CCR2, characteristicCCRs2);
		Servo servo3 = Servo(&htim1.Instance->CCR3, characteristicCCRs3);

		Servo servos[NUM_HINGES_IN_LEGS] = { servo1, servo2, servo3 };

		FrontLeftLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion

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

};



//uint8_t Speed = 88;
//uint8_t ui8 = 130;
//int8_t i8=130;
//uint16_t ui16 = 65000;
//int16_t i16 = 65000;
