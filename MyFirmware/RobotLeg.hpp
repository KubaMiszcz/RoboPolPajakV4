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
	Vector3D OffsetFromRobotOrigin;
	float L[NumHingesInLegs];
	Servo* Servos[NumHingesInLegs];
	Vector3D CurrentFootPosition;
	RobotLeg() {
		//todo remove parameterless ctor and make one with all critical parameters
		//for (size_t i = 0; i < NumHingesInLegs; i++)
		//{
		//	Servo* s = new Servo;
		//	Servos[i] = s;
		//}
	};
	Vector3D GetFootPosition() {
		//todo:tutaj straightkin
		return CurrentFootPosition;
	};
	void SetPosition(Vector3D pos) {
		//todo:tutaj kininv
		//todo
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


