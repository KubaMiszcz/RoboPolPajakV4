#pragma once
#include "RobotLeg.hpp"
class Robot {
public:
	Vector3D CurrentCOGPosition; //todo update this somehow?
	RobotLeg FrontLeftLeg;
	RobotLeg FrontRightLeg;
	RobotLeg RearRightLeg;
	RobotLeg RearLeftLeg;
	RobotLeg AllLegs[NUM_LEGS];
	uint8_t Delay = 3; //HAL_Delay(Delay); // fix it with time dependent, queue or sth non blocking
private:
	uint8_t movementStage = 0;
	uint8_t moveCGforBalance = 20;
	Vector3D moveCGVector;
	float_t moveForward;
	float_t moveUp;

	//debug only

public:
	Robot() {}

	void InitMCUPeripherals() {}

	void InitRobotProperties() {
		Vector3D offsetFromOrigin;
		Servo servos[NUM_HINGES_IN_LEG];

		//Construction Properties [mm]
		int16_t offsetX = 35; int16_t offsetY = 35; int16_t offsetZ = -22; //[mm]
		uint16_t lengths[NUM_HINGES_IN_LEG] = { 32, 64, 123 }; //[mm]

#pragma region FrontRightLeg
		offsetFromOrigin = Vector3D(offsetX, offsetY, offsetZ);

		uint16_t characteristicCCRsServo5186[5] = { 6911, 5350, 4025, 2825, 1612 };
		uint16_t characteristicCCRsServo5185[5] = { 7164, 5650, 4205, 2850, 1767 };
		uint16_t characteristicCCRsServo5184Reversed[5] = { 1921, 3275, 4650, 5975, 7579 };

		servos[0] = Servo(&htim1.Instance->CCR1, characteristicCCRsServo5186);
		servos[1] = Servo(&htim1.Instance->CCR2, characteristicCCRsServo5185);
		servos[2] = Servo(&htim1.Instance->CCR3, characteristicCCRsServo5184Reversed);

		FrontRightLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion FrontRightLeg

#pragma region FrontLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, offsetY, offsetZ);

		uint16_t characteristicCCRsServo5135[5] = { 7121, 5325, 3975, 2825, 1678 };
		uint16_t characteristicCCRsServo5181[5] = { 6977, 5325, 3975, 2725, 1530 };
		uint16_t characteristicCCRsServo5132Reversed[5] = { 1860, 3300, 4575, 5850, 7365 };
		servos[0] = Servo(&htim2.Instance->CCR1, characteristicCCRsServo5135);
		servos[1] = Servo(&htim2.Instance->CCR2, characteristicCCRsServo5181);
		servos[2] = Servo(&htim2.Instance->CCR3, characteristicCCRsServo5132Reversed);

		FrontLeftLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion FrontLeftLeg

#pragma region RearRightLeg
		offsetFromOrigin = Vector3D(offsetX, -offsetY, offsetZ);

		uint16_t characteristicCCRsServo5134[5] = { 6600, 5125, 3850, 2750, 1650 };
		uint16_t characteristicCCRsServo5133[5] = { 7894, 5930, 4550, 3340, 2094 };
		uint16_t characteristicCCRsServo5183Reversed[5] = { 1880, 3175, 4475, 5800, 7498 };

		servos[0] = Servo(&htim3.Instance->CCR1, characteristicCCRsServo5134);
		servos[1] = Servo(&htim3.Instance->CCR2, characteristicCCRsServo5133);
		servos[2] = Servo(&htim3.Instance->CCR3, characteristicCCRsServo5183Reversed);

		RearRightLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion RearRightLeg

#pragma region RearLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, -offsetY, offsetZ);

		uint16_t characteristicCCRsServo5131[5] = { 7391, 5650, 4210, 2900, 1753 };
		uint16_t characteristicCCRsServo5187[5] = { 7442, 5650, 4325, 3025, 1838 };
		uint16_t characteristicCCRsServo5182Reversed[5] = { 1640, 2900, 4100, 5375, 6928 };

		servos[0] = Servo(&htim1.Instance->CCR4, characteristicCCRsServo5131);
		servos[1] = Servo(&htim2.Instance->CCR4, characteristicCCRsServo5187);
		servos[2] = Servo(&htim3.Instance->CCR4, characteristicCCRsServo5182Reversed);

		RearLeftLeg = RobotLeg(offsetFromOrigin, lengths, servos);
#pragma endregion RearLeftLeg
		AllLegs[0] = FrontLeftLeg;
		AllLegs[1] = FrontRightLeg;
		AllLegs[2] = RearRightLeg;
		AllLegs[3] = RearLeftLeg;
	}

	void MoveGravityCenterByVector(float_t x, float_t y, float_t z) {
		MoveGravityCenterByVector(Vector3D(x, y, z));
	}

	/// ********************************************************************************
	/// <summary>
	/// move legs in opposite side than passed Vector,
	/// it means same as that legs stays in place b
	/// but Robot Center of Gravity moves by 
	/// passed vector
	/// </summary>
	/// <param name="v">direction Vector for move CG</param>
	/// <created>KubaMiszcz,2018-05-25</created>
	/// <changed>KubaMiszcz,2018-05-25</changed>
	void MoveGravityCenterByVector(Vector3D vec) {
		vec.Negate();
		for (size_t i = 0; i < NUM_LEGS; i++)
		{
			AllLegs[i].MoveByVector(vec);
		}
	}

	bool IsMoving() const {
		bool result = false;
		for (size_t i = 0; i < NUM_LEGS; i++)
		{
			if (AllLegs[i].IsMoving()) result = true;
		}
		return result;
	}

	bool IsInDestination() const {
		return !IsMoving();
	}

	void MoveOneLeg(RobotLeg leg, float_t x = 0, float_t y = 30, float_t z = 30) {
		MoveOneLeg(leg, Vector3D(x, y, z));
	}

	uint8_t MoveOneLeg(RobotLeg robotLeg, Vector3D destination) {
		switch (movementStage)
		{
		case 0: {//prepare sequence parameters
			moveForward = destination.Y;
			moveUp = destination.Z;

			//simultaneously move CG slightly oppose to moving leg -> right back
			float_t x = -1 * sgn(robotLeg.LegOffsetVectorFromRobotOrigin.X)*moveCGforBalance;
			float_t y = -1 * sgn(robotLeg.LegOffsetVectorFromRobotOrigin.Y)*moveCGforBalance;
			moveCGVector = Vector3D(x, y, 0); //check: is it permanent? or lost in case 1?
			MoveGravityCenterByVector(moveCGVector);
			movementStage = 1;
		}break;
		case 1:
			if (IsInDestination()) {
				robotLeg.MoveByVector(0, 0, moveUp);
				movementStage++;
			}
			break;
		case 2:
			//start lift up leg, move formawr, lift down
			if (robotLeg.IsInDestination()) {
				robotLeg.MoveByVector(0, moveForward, 0);
				movementStage++;
			}
			break;
		case 3:
			if (robotLeg.IsInDestination()) {
				robotLeg.MoveByVector(0, 0, -moveUp);
				movementStage++;
			}
			break;
		case 4:
			if (robotLeg.IsInDestination()) {
				MoveGravityCenterByVector(moveCGVector.Negate());
				movementStage++;
			}
			break;
		case 5: //end sequence and reset parameters
			if (IsInDestination()) {
				movementStage = 0;
			}
			return 1;
			break;
		default:
			break;
		}
		return 0;
	}



	//void OneStepForward(float_t moveUp = 30, float_t moveForward = 30) {
	//	/// #################################
	//	/// OneStepForward sequence

	//	//############################### START 1st FrontLeftLeg ###########################

	//	//######################### END 1ST FrontLeftLeg ########################################

	//	//######################## START 2nd FrontRightLeg ###################################
	//	//move CG slighly oppose to moving leg -> left
	//	moveCGVector = Vector3D(-moveCG, moveCG, 0).Add(-moveCG, -moveCG, 0).Negate();
	//	FrontLeftLeg.MoveByVector(moveCGVector);
	//	FrontRightLeg.MoveByVector(moveCGVector);
	//	RearRightLeg.MoveByVector(moveCGVector);
	//	RearLeftLeg.MoveByVector(moveCGVector);
	//	//lift up leg, move formawr, lift down
	//	FrontRightLeg.MoveByVector(0, 0, moveUp);
	//	FrontRightLeg.MoveByVector(0, moveForward, 0);
	//	FrontRightLeg.MoveByVector(0, 0, moveDown);
	//	//######################### END 2nd FrontRightLeg ########################################

	//	//######################## START 3nd RearRightLeg ###################################
	//	//move CG slighly oppose to moving leg -> left
	//	moveCGVector = Vector3D(moveCG, moveCG, 0).Add(-moveCG, moveCG, 0).Negate();
	//	FrontLeftLeg.MoveByVector(moveCGVector);
	//	FrontRightLeg.MoveByVector(moveCGVector);
	//	RearRightLeg.MoveByVector(moveCGVector);
	//	RearLeftLeg.MoveByVector(moveCGVector);
	//	//lift up leg, move formawr, lift down
	//	RearRightLeg.MoveByVector(0, 0, moveUp);
	//	RearRightLeg.MoveByVector(0, moveForward, 0);
	//	RearRightLeg.MoveByVector(0, 0, moveDown);
	//	//######################### END 3nd RearRightLeg ########################################

	//	//######################## START 4nd RearLeftLeg ###################################
	//	//move CG slighly oppose to moving leg -> left
	//	moveCGVector = Vector3D(moveCG, -moveCG, 0).Add(moveCG, moveCG, 0).Negate();
	//	FrontLeftLeg.MoveByVector(moveCGVector);
	//	FrontRightLeg.MoveByVector(moveCGVector);
	//	RearRightLeg.MoveByVector(moveCGVector);
	//	RearLeftLeg.MoveByVector(moveCGVector);
	//	//lift up leg, move formawr, lift down
	//	RearLeftLeg.MoveByVector(0, 0, moveUp);
	//	RearLeftLeg.MoveByVector(0, moveForward, 0);
	//	RearLeftLeg.MoveByVector(0, 0, moveDown);
	//	//######################### END 4nd RearLeftLeg ########################################
	//}

	void SetPoseStandUp(float_t height = 100) {
		// ##################### START Pose stand Up #########################
		MoveGravityCenterByVector(Vector3D(0, 0, height));
		// ##################### END Pose stand Up #########################
	}


	void SetPoseLayDown() {
		//##################### START Pose lay down #########################
		//cos jka kroki tylko nogi wszerz ale musi tuptac i chyba ten srodek ciezkosci balansowac
		//jak dopracuej kroki to wteyd to
		//##################### END Pose lay down #########################
	}
};

//uint8_t Speed = 88;
//uint8_t ui8 = 130;
//int8_t i8=130;
//uint16_t ui16 = 65000;
//int16_t i16 = 65000;
