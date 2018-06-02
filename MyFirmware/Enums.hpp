/*
 * Enums.hpp
 *
 *  Created on: May 6, 2018
 *      Author: KubaMiszcz
 */
#pragma once
 //use prefixes in enums to prevent cross names
// using enum class is more safe but need some code in use
 enum e_SingleStepStages 
 {
	 XX_InStandby=0,
	 XX_EndSequence
 };

 enum e_SingleLegMovementStages //convert to enum class to avoid cross names
 {
	 e_SingleLeg_InStandby = 0,
	 e_SingleLeg_SetSequenceParameters,
	 e_SingleLeg_MoveCGforBalance,
	 e_SingleLeg_MoveLeg,
	 e_SingleLeg_EndSequence
 };

 enum e_RobotLegs
 {
	 e_FrontLeftLeg=0, e_FrontRightLeg, e_RearRightLeg, e_RearLeftLeg
 };

enum e_Poses
{
	e_Neutral=0,
	e_StandUp,
	e_LayDown
};

//enum class EnumStates {
//	IsInDestination, IsMoving
//};
//
//enum class MyEnumClass
//{
//	my1,my2
//};

//typedef enum {
//	IsInDestination, IsMoving
//} EnumStates;


