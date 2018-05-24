#pragma once
#include "RobotLeg.hpp"
class Robot
{
  public:
	Vector3D CurrentPosition;
	RobotLeg FrontLeftLeg;
	RobotLeg FrontRightLeg;
	RobotLeg RearRightLeg;
	RobotLeg RearLeftLeg;
	uint8_t delay;
	//HAL_Delay(delay); // fix it with time dependent, queue or sth non blocking

	//debug only
	//RobotLeg AllLegs[NUM_LEGS];

	Robot() {};

	void InitMCUPeripherals() {
	};
	void InitRobotProperties() {
		Vector3D offsetFromOrigin = Vector3D();
		int16_t offsetX = 35; int16_t offsetY = 35; int16_t offsetZ = -22;
		Servo servos[NUM_HINGES_IN_LEGS];
		uint16_t lengths[NUM_HINGES_IN_LEGS] = {32, 64, 123};

#pragma region FrontRightLeg
		offsetFromOrigin = Vector3D(offsetX, offsetY, offsetZ);

		uint16_t characteristicCCRsServo5186[5] = {6911, 5350, 4025, 2825, 1612};
		uint16_t characteristicCCRsServo5185[5] = {7164, 5650, 4205, 2850, 1767};
		uint16_t characteristicCCRsServo5184Reversed[5] = {1921, 3275, 4650, 5975, 7579};

		servos[0] = Servo(&htim1.Instance->CCR1, characteristicCCRsServo5186);
		servos[1] = Servo(&htim1.Instance->CCR2, characteristicCCRsServo5185);
		servos[2] = Servo(&htim1.Instance->CCR3, characteristicCCRsServo5184Reversed);

		FrontRightLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion

#pragma region FrontLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, offsetY, offsetZ);

		uint16_t characteristicCCRsServo5135[5] = {7121, 5325, 3975, 2825, 1678};
		uint16_t characteristicCCRsServo5181[5] = {6977, 5325, 3975, 2725, 1530};
		uint16_t characteristicCCRsServo5132Reversed[5] = {1860, 3300, 4575, 5850, 7365};
		servos[0] = Servo(&htim2.Instance->CCR1, characteristicCCRsServo5135);
		servos[1] = Servo(&htim2.Instance->CCR2, characteristicCCRsServo5181);
		servos[2] = Servo(&htim2.Instance->CCR3, characteristicCCRsServo5132Reversed);

		FrontLeftLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion

#pragma region RearRightLeg
		offsetFromOrigin = Vector3D(offsetX, -offsetY, offsetZ);

		uint16_t characteristicCCRsServo5134[5] = {6600, 5125, 3850, 2750, 1650};
		uint16_t characteristicCCRsServo5133[5] = {7894, 5930, 4550, 3340, 2094};
		uint16_t characteristicCCRsServo5183Reversed[5] = {1880, 3175, 4475, 5800, 7498};

		servos[0] = Servo(&htim3.Instance->CCR1, characteristicCCRsServo5134);
		servos[1] = Servo(&htim3.Instance->CCR2, characteristicCCRsServo5133);
		servos[2] = Servo(&htim3.Instance->CCR3, characteristicCCRsServo5183Reversed);

		RearRightLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion

#pragma region RearLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, -offsetY, offsetZ);

		uint16_t characteristicCCRsServo5131[5] = {7391, 5650, 4210, 2900, 1753};
		uint16_t characteristicCCRsServo5187[5] = {7442, 5650, 4325, 3025, 1838};
		uint16_t characteristicCCRsServo5182Reversed[5] = {1640, 2900, 4100, 5375, 6928};

		servos[0] = Servo(&htim1.Instance->CCR4, characteristicCCRsServo5131);
		servos[1] = Servo(&htim2.Instance->CCR4, characteristicCCRsServo5187);
		servos[2] = Servo(&htim3.Instance->CCR4, characteristicCCRsServo5182Reversed);

		RearLeftLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion
	};

	void MoveCGByVector(float_t x, float_t y, float_t z) {
		MoveCGByVector(Vector3D(x, y, z));
	}

	void MoveCGByVector(Vector3D v) {
		//todo implement
		//move legs inverse, legs stays in place but CG robot moves
	}

	bool IsMoving() {
		return (FrontLeftLeg.IsMoving || FrontRightLeg.IsMoving || RearRightLeg.IsMoving || RearLeftLeg.IsMoving) ? true : false;
	}

	void StepForward() {
	};
};

//uint8_t Speed = 88;
//uint8_t ui8 = 130;
//int8_t i8=130;
//uint16_t ui16 = 65000;
//int16_t i16 = 65000;
