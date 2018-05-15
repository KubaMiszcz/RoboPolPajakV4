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
	Vector3D OffsetVectorFromRobotOrigin;
	float_t OffsetAngleFromRobotOrigin_RAD;
	uint16_t Length[NUM_HINGES_IN_LEGS];
	Servo* Servos[NUM_HINGES_IN_LEGS];
	Vector3D CurrentFootPosition;
private:
	uint32_t Length1Square;
	uint32_t Length2Square;

	//RobotLeg() {
	//	//todo remove parameterless ctor and make one with all critical parameters
	//	//for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
	//	//{
	//	//	Servo* s = new Servo;
	//	//	Servos[i] = s;
	//	//}
	//};
public:
	RobotLeg(Vector3D offsetFromRobotOrigin, uint16_t lengths[NUM_HINGES_IN_LEGS], Servo* servos[NUM_HINGES_IN_LEGS]) {
		OffsetVectorFromRobotOrigin = offsetFromRobotOrigin;
		OffsetAngleFromRobotOrigin_RAD = myAtan2(OffsetVectorFromRobotOrigin.Y, OffsetVectorFromRobotOrigin.X);

		for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
		{
			Length[i] = lengths[i];
		}
		Length1Square = myPowToSecond(Length[1], 2);
		Length2Square = myPowToSecond(Length[2], 2);

		for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
		{
			//Servo* s = new Servo;
			Servos[i] = servos[i];
		}

	};

	Vector3D GetFootPosition() {
		return CurrentFootPosition;
	};

	void SetPosition(Vector3D dest) {
		//! INVERSE KINEMATIC
		//Vector3D O1 = OffsetVectorFromRobotOrigin;
		Vector3D destFromOriginS1 = dest.Subtract(OffsetVectorFromRobotOrigin);

		float_t Theta_RAD[3];
		//atan2(y,x)
		Theta_RAD[0] = myAtan2(destFromOriginS1.Y, destFromOriginS1.X) - OffsetAngleFromRobotOrigin_RAD;

		Vector3D originS2 = Vector3D(OffsetVectorFromRobotOrigin.X + Length[0] * cos(Theta_RAD[0]),
			OffsetVectorFromRobotOrigin.Y + Length[0] * sin(Theta_RAD[0]), OffsetVectorFromRobotOrigin.Z);
		
		Vector3D destFromOriginS2 = dest.Subtract(originS2);

		float_t magnitudeOriginS2toDest = sqrt(myPowToSecond(destFromOriginS2.X, 2) + myPowToSecond(destFromOriginS2.Y, 2));
		if (magnitudeOriginS2toDest > sqrt(Length1Square + Length2Square))
			return;

		//(locX^2 + locY^2 + locZ^2 - L1^2 - L2^2) / 	(2* L1 * L2)
		float_t cos3 = (pow(magnitudeOriginS2toDest, 2) + myPowToSecond(destFromOriginS2.Z, 2) - Length1Square - Length2Square) / (2 * Length[1] * Length[2]);

		//= - sqrt(1 - c3^2)
		float_t sin3 = -sqrt(1 - pow(cos3, 2));

		//= atan2(locZ , sqrt(locX^2 + locZ^2) - atan2(L2*c3, L1+L2*c3)
		Theta_RAD[1] = atan2(destFromOriginS2.Z, magnitudeOriginS2toDest) - atan2(Length[2] * sin3, Length[1] + Length[2] * cos3);
		
		//atan2(sin3, cos3);
		//!plus 90degrees because servo 0posioton is 90degree offset 
		Theta_RAD[2] = atan2(sin3, cos3)+90/TO_DEGREES;
		
		for (size_t i = 0; i < NUM_HINGES_IN_LEGS; i++)
		{
			Servos[i]->SetCCRValuebyAngle(ToDegrees(Theta_RAD[i]));
			Servos[i]->theta = ToDegrees(Theta_RAD[i]);
		}

		CurrentFootPosition = dest;
	};

	//=====================================

	States State;


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
	States State;
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


