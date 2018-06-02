#pragma once
#include "RobotLeg.hpp"
#include "MathHelpers.hpp"
#include "Enums.hpp"
#include "GlobalConstants.hpp"

class Robot {
public:
	Vector3D CurrentCOGPosition; //todo update this somehow?
	RobotLeg AllLegs[NUM_LEGS];
	//uint8_t Delay = 1; //HAL_Delay(Delay); // fix it with time dependent, queue or sth non blocking

private:
	bool isInStepSequence;
	bool isInSingleLegStepSequence;
	bool isOnRoute;
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
		int16_t offsetX = LEG_OFFSET_FROM_ORIGIN_IN_X;
		int16_t offsetY = LEG_OFFSET_FROM_ORIGIN_IN_Y;
		int16_t offsetZ = LEG_OFFSET_FROM_ORIGIN_IN_Z; //[mm]
		//uint16_t lengths[NUM_HINGES_IN_LEG] = {
		//	LEG_SEGMENT_0_LENGTH,
		//	LEG_SEGMENT_1_LENGTH,
		//	LEG_SEGMENT_2_LENGTH
		//};

#pragma region FrontLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, offsetY, offsetZ);

		servos[0] = Servo(&htim2.Instance->CCR1, SERVO_5135_CHARACTERISTIC_CCRS);
		servos[1] = Servo(&htim2.Instance->CCR2, SERVO_5181_CHARACTERISTIC_CCRS);
		servos[2] = Servo(&htim2.Instance->CCR3, SERVO_5132_CHARACTERISTIC_CCRS);

		AllLegs[e_FrontLeftLeg] = RobotLeg(offsetFromOrigin, LEG_SEGMENT_LENGTHS, servos);
#pragma endregion FrontLeftLeg

#pragma region FrontRightLeg
		offsetFromOrigin = Vector3D(offsetX, offsetY, offsetZ);

		servos[0] = Servo(&htim1.Instance->CCR1, SERVO_5186_CHARACTERISTIC_CCRS);
		servos[1] = Servo(&htim1.Instance->CCR2, SERVO_5185_CHARACTERISTIC_CCRS);
		servos[2] = Servo(&htim1.Instance->CCR3, SERVO_5184_CHARACTERISTIC_CCRS);

		AllLegs[e_FrontRightLeg] = RobotLeg(offsetFromOrigin, LEG_SEGMENT_LENGTHS, servos);
#pragma endregion FrontRightLeg


#pragma region RearRightLeg
		offsetFromOrigin = Vector3D(offsetX, -offsetY, offsetZ);

		servos[0] = Servo(&htim3.Instance->CCR1, SERVO_5134_CHARACTERISTIC_CCRS);
		servos[1] = Servo(&htim3.Instance->CCR2, SERVO_5133_CHARACTERISTIC_CCRS);
		servos[2] = Servo(&htim3.Instance->CCR3, SERVO_5183_CHARACTERISTIC_CCRS);

		AllLegs[e_RearRightLeg] = RobotLeg(offsetFromOrigin, LEG_SEGMENT_LENGTHS, servos);
#pragma endregion RearRightLeg

#pragma region RearLeftLeg
		offsetFromOrigin = Vector3D(-offsetX, -offsetY, offsetZ);

		servos[0] = Servo(&htim1.Instance->CCR4, SERVO_5131_CHARACTERISTIC_CCRS);
		servos[1] = Servo(&htim2.Instance->CCR4, SERVO_5187_CHARACTERISTIC_CCRS);
		servos[2] = Servo(&htim3.Instance->CCR4, SERVO_5182_CHARACTERISTIC_CCRS);

		AllLegs[e_RearLeftLeg] = RobotLeg(offsetFromOrigin, LEG_SEGMENT_LENGTHS, servos);
#pragma endregion RearLeftLeg

		//AllLegs[0] = &FrontLeftLeg;
		//AllLegs[1] = &FrontRightLeg;
		//AllLegs[2] = &RearRightLeg;
		//AllLegs[3] = &RearLeftLeg;

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
			//AllLegs[i]->MoveByVector(vec);//check 
			AllLegs[i].MoveByVector(vec);

		}
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
			float_t x = -1 * signum(robotLeg.LegOffsetVectorFromRobotOrigin.X) * moveCGforBalance;
			float_t y = -1 * signum(robotLeg.LegOffsetVectorFromRobotOrigin.Y) * moveCGforBalance;
			moveCGVector = Vector3D(x, y, 0); //check: is it permanent? or lost in case 1?
			MoveGravityCenterByVector(moveCGVector);
			movementStage = 1;
		}
				break;
				//case 1:
				//	if (IsInDestination()) {
				//		robotLeg.MoveByVector(0, 0, moveUp);
				//		movementStage++;
				//	}
				//	break;
				//case 2:
				//	//start lift up leg, move formawr, lift down
				//	if (robotLeg.IsInDestination()) {
				//		robotLeg.MoveByVector(0, moveForward, 0);
				//		movementStage++;
				//	}
				//	break;
				//case 3:
				//	if (robotLeg.IsInDestination()) {
				//		robotLeg.MoveByVector(0, 0, -moveUp);
				//		movementStage++;
				//	}
				//	break;
				//case 4:
				//	if (robotLeg.IsInDestination()) {
				//		MoveGravityCenterByVector(moveCGVector.Negate());
				//		movementStage++;
				//	}
				//	break;
				//case 5: //end sequence and reset parameters
				//	if (IsInDestination()) {
				//		movementStage = 0;
				//	}
				//	return 1;
				//	break;
		default:
			break;
		}
		return 0;
	}



	bool xxxIsMoving() const {
		bool result = false;
		for (size_t i = 0; i < NUM_LEGS; i++)
		{
			//if (AllLegs[i]->IsMoving()) result = true; //check
			if (AllLegs[i].IsMoving()) result = true;
		}
		return result;
	}

	bool IsInStepSequence() const {
		return isInStepSequence;
	}

	bool IsStepSequenceFinished() const {
		return !isInStepSequence;
	}

	bool IsInSingleLegStepSequence() const {
		return isInSingleLegStepSequence;
	}

	bool IsSingleLegStepSequenceFinished() const {
		return !isInSingleLegStepSequence;
	}

	bool IsOnRoute() const {
		return isOnRoute;
	}

	bool IsInRouteDestination() const {
		return !isOnRoute;
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


	void SetPoseNeutral() {
		//##################### START Pose lay down #########################
		//cos jka kroki tylko nogi wszerz ale musi tuptac i chyba ten srodek ciezkosci balansowac
		//jak dopracuej kroki to wteyd to
		//##################### END Pose lay down #########################
	}

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
