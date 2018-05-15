/*
 * Servo.hpp
 *
 *  Created on: May 6, 2018
 *      Author: KubaMiszcz
 */

#pragma once
#include "Enums.hpp"

class Servo {
public:
	uint16_t degPos90CCR;
	uint16_t degPos45CCR;
	uint16_t deg0CCR;
	uint16_t degNeg45CCR;
	uint16_t degNeg90CCR;
	volatile uint32_t* ptrCCR;

	//?debug Only
	float_t theta;
	
	Servo() {};

	Servo(volatile uint32_t* ccr, uint16_t characteristicCCRs[5]) { 
		ptrCCR = ccr; 
		degPos90CCR = characteristicCCRs[0];
		degPos45CCR = characteristicCCRs[1];
		deg0CCR = characteristicCCRs[2];
		degNeg45CCR = characteristicCCRs[3];
		degNeg90CCR = characteristicCCRs[4];	
		*ptrCCR = deg0CCR;
	};

	void SetCCRValuebyAngle(float_t angle) {
		if (angle >= 0)
		{
			if (angle >=90) *ptrCCR = degPos90CCR;
			else if (angle > 45) *ptrCCR = mapAngleToCCR(angle, 45, 90, degPos45CCR, degPos90CCR);
			else *ptrCCR = mapAngleToCCR(angle, 0, 45, deg0CCR, degPos45CCR);
		}
		if (angle < 0)
		{
			if (angle <= -90) *ptrCCR = degNeg90CCR;
			if (angle < -45) *ptrCCR = mapAngleToCCR(angle, -45, -90, degNeg45CCR, degNeg90CCR);
			else *ptrCCR = mapAngleToCCR(angle, 0, -45, deg0CCR, degNeg45CCR);
		}
	};

	uint16_t GetCCRValue() {
		return *ptrCCR;
	};



	//============================================
	EnumStates State;
};







/*

#ifndef __SERVO_H_
#define __SERVO_H_
#include "enums.h"

typedef uint16_t(*Get_uint16_t_value)(uint32_t*);


typedef struct {
float CurrentAngle;
EnumStates State;
uint32_t* pDutyCCR;
//============================================
TIM_HandleTypeDef* tim;
uint32_t channel;
uint16_t minCCR;
uint16_t maxCCR;
Get_uint16_t_value GetDutyValue;
} Servo;

void GetAngle(Servo* s) {
}
void SetAngle(Servo* s, float angle) {
}
void SetDuty(Servo* s) {
}

uint16_t GetDutyValue_(uint32_t* s) {
return 121;
}

*/

/*
 Jak utworzyæ definicjê wskaŸnika na funkcjê?
 Mamy deklaracjê funkcji:
 int mojaFunkcja( float a, int b, const char * c );
 Oczyszczamy j¹ z nazw argumentów:
 int mojaFunkcja( float, int, const char * );
 Nazwê funkcji zmieniamy na jak¹œ now¹ nazwê i dopisujemy na pocz¹tku typedef:
 typedef int nazwaTypuT( float, int, const char * );
 Nazwê typu umieszczamy w nawiasach zaokr¹glonych:
 typedef int( nazwaTypuT )( float, int, const char * );
 Przed nazw¹ typu i jednoczeœnie za wstawionym nawiasem otwieraj¹cym, dostawionym w poprzednim kroku - umieszczamy gwiazdkê:
 typedef int( * nazwaTypuT )( float, int, const char * );
 Jak zapisaæ adres funkcji do wskaŸnika?
 nazwaTypuT pWskaznikNaFunkcje = mojaFunkcja;

 Jak wywo³aæ funkcjê zapisan¹ we wskaŸniku?
 int iWynik = pWskaznikNaFunkcje( 123.4f, 567, "Koniec" );
 */

