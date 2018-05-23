/*
 * RobotArm.hpp
 *
 *  Created on: May 6, 2018
 *      Author: KubaMiszcz
 */

#pragma once
#include "Servo.hpp"

class RobotLeg {
public:
	Vector3D LegOffsetVectorFromRobotOrigin;
	//float_t OffsetAngleFromRobotOrigin_RAD;
	uint16_t Length[NUM_HINGES_IN_LEGS];
	Servo Servos[NUM_HINGES_IN_LEGS];
	Vector3D CurrentFootPosition;
	bool IsMoving;

private:
	uint32_t Length1Square;
	uint32_t Length2Square;

	//debug only
	float_t Theta_DEG[3];


public:
	RobotLeg() {};

	RobotLeg(Vector3D offsetFromRobotOrigin, uint16_t lengths[NUM_HINGES_IN_LEGS], Servo servos[NUM_HINGES_IN_LEGS]) {
		LegOffsetVectorFromRobotOrigin = offsetFromRobotOrigin;
		//OffsetAngleFromRobotOrigin_RAD = myAtan2(LegOffsetVectorFromRobotOrigin.Y, LegOffsetVectorFromRobotOrigin.X);

		for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
		{
			Length[i] = lengths[i];
			Servos[i] = servos[i];
		}
		Length1Square = pow((float_t)Length[1], 2);
		Length2Square = pow((float_t)Length[2], 2);
	};

	Vector3D GetFootPosition() {
		return CurrentFootPosition;
	};
	
	void SetPosition(Vector3D dest) {
		//! INVERSE KINEMATIC
		float_t OffsetAngleFromRobotOrigin_RAD = atan2(LegOffsetVectorFromRobotOrigin.Y, LegOffsetVectorFromRobotOrigin.X);

		//Vector3D O1 = LegOffsetVectorFromRobotOrigin;
		Vector3D destinationPointFromOriginS1 = dest;
		destinationPointFromOriginS1.Subtract(LegOffsetVectorFromRobotOrigin);

		float_t Theta_RAD[3];
		//atan2(y,x)
		Theta_RAD[0] = atan2(destinationPointFromOriginS1.Y, destinationPointFromOriginS1.X);

		Vector3D originS2 = Vector3D(LegOffsetVectorFromRobotOrigin.X + Length[0] * cos(Theta_RAD[0]),
			LegOffsetVectorFromRobotOrigin.Y + Length[0] * sin(Theta_RAD[0]), LegOffsetVectorFromRobotOrigin.Z);

		Vector3D destinationPointFromOriginS2 = dest;
		destinationPointFromOriginS2.Subtract(originS2);

		float_t destinationPointFromOriginS2_X_Square = pow(destinationPointFromOriginS2.X, 2);
		float_t destinationPointFromOriginS2_Y_Square = pow(destinationPointFromOriginS2.Y, 2);

		float_t magnitudeOriginS2toDestination = sqrt(destinationPointFromOriginS2_X_Square + destinationPointFromOriginS2_Y_Square + pow(destinationPointFromOriginS2.Z, 2));

		//check if is dest point in leg range
		if (magnitudeOriginS2toDestination > Length[1] + Length[2])
			return;

		//(locX^2 + locY^2 + locZ^2 - L1^2 - L2^2) / 	(2* L1 * L2)
		float_t cos3 = (pow(magnitudeOriginS2toDestination, 2) - Length1Square - Length2Square) / (2 * Length[1] * Length[2]);

		//= - sqrt(1 - c3^2)
		float_t sin3 = -sqrt(1 - pow(cos3, 2));

		//= atan2(locZ , sqrt(locX^2 + locZ^2) - atan2(L2*c3, L1+L2*c3)
		Theta_RAD[1] = atan2(destinationPointFromOriginS2.Z, sqrt(destinationPointFromOriginS2_X_Square + destinationPointFromOriginS2_Y_Square)) - atan2(Length[2] * sin3, Length[1] + Length[2] * cos3);

		//atan2(sin3, cos3);
		Theta_RAD[2] = atan2(sin3, cos3);

		//!minus 45degrees because servo 0posioton is 45degree offset from global X
		Theta_RAD[0] = OffsetAngleFromRobotOrigin_RAD - Theta_RAD[0];
		if (Theta_RAD[0] < -M_PI)
		{
			Theta_RAD[0] = Theta_RAD[0] + 2 * M_PI;
		}
		else if (Theta_RAD[0] > M_PI)
		{
			Theta_RAD[0] = Theta_RAD[0] - 2 * M_PI;
		}
		
		//!plus 90degrees because servo 0posioton is 90degree offset 
		Theta_RAD[2] += M_PI_2; // 90 / TO_DEGREES;

		for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
		{
			Servos[i].SetCCRValueByAngle_RAD(Theta_RAD[i]);
			Servos[i].theta = ToDegrees(Theta_RAD[i]);	//debug only
			Theta_DEG[i] = ToDegrees(Theta_RAD[i]);	//debug only
		}

		CurrentFootPosition = dest;
	};
};

























/*
#ifndef __ROBOTARM_H__
#define __ROBOTARM_H__
#include "Vector.hpp"
#include "servo.h"
#include "enums.h"

typedef struct {
	float X_offsetFromRobotOrigin;
	float Y_offsetFromRobotOrigin;
	EnumStates State;
	float L1;
	float L2;
	float L3;
	Servo Servos[3];
	Vector3D CurrentPosition;
} RobotArm;

void SetPosition(RobotArm* ra, uint16_t X, uint16_t Y, uint16_t Z) {
	//todo
}

void SetPosition_Vector3D(RobotArm* ra, Vector3D v) {
	ra->CurrentPosition = v;
}

Vector3D GetPosition(RobotArm* ra) {
	Vector3D a;
	return ra->CurrentPosition;
}


void SetAngles(RobotArm* ra, float th1, float th2, float th3) {
	//todo
}


#endif /* __ROBOTARM_H__ */


