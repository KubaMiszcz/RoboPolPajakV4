/*
 * Servo.hpp
 *
 *  Created on: May 6, 2018
 *      Author: KubaMiszcz
 */

#pragma once
 //#include "Enums.hpp"

class Servo {
public:
	uint16_t degPos90CCR;
	uint16_t degPos45CCR;
	uint16_t deg0CCR;
	uint16_t degNeg45CCR;
	uint16_t degNeg90CCR;
	volatile uint32_t *ptrCCR;

	//?debug Only
	float_t theta;

	Servo() {}

	Servo(volatile uint32_t *ccr, uint16_t characteristicCCRs[5]) {
		ptrCCR = ccr;
		degPos90CCR = characteristicCCRs[0];
		degPos45CCR = characteristicCCRs[1];
		deg0CCR = characteristicCCRs[2];
		degNeg45CCR = characteristicCCRs[3];
		degNeg90CCR = characteristicCCRs[4];
		//*ptrCCR = deg0CCR;
	};

	void SetCCRValueByAngle_RAD(float_t angle_RAD) {
		if (angle_RAD >= 0) {
			if (angle_RAD >= M_PI_2) *ptrCCR = degPos90CCR;
			else if (angle_RAD > M_PI_4) *ptrCCR = mapToFloat_t(angle_RAD, M_PI_4, M_PI_2, degPos45CCR, degPos90CCR);
			else *ptrCCR = mapToFloat_t(angle_RAD, 0, M_PI_4, deg0CCR, degPos45CCR);
		}
		else {
			if (angle_RAD <= -M_PI_2) *ptrCCR = degNeg90CCR;
			else if (angle_RAD < -M_PI_4) *ptrCCR = mapToFloat_t(angle_RAD, -M_PI_4, -M_PI_2, degNeg45CCR, degNeg90CCR);
			else *ptrCCR = mapToFloat_t(angle_RAD, 0, -M_PI_4, deg0CCR, degNeg45CCR);
		}
	}

	void SetCCRValueByAngle_DEG(float_t angle) {
		if (angle >= 0) {
			if (angle >= 90) *ptrCCR = degPos90CCR;
			else if (angle > 45) *ptrCCR = mapToFloat_t(angle, 45, 90, degPos45CCR, degPos90CCR);
			else *ptrCCR = mapToFloat_t(angle, 0, 45, deg0CCR, degPos45CCR);
		}
		if (angle < 0) {
			if (angle <= -90) *ptrCCR = degNeg90CCR;
			else if (angle < -45) *ptrCCR = mapToFloat_t(angle, -45, -90, degNeg45CCR, degNeg90CCR);
			else *ptrCCR = mapToFloat_t(angle, 0, -45, deg0CCR, degNeg45CCR);
		}
	}

	//=====debug only==========================
	uint16_t GetCCRValue() const {
		return *ptrCCR;
	}

	//TODO check this
		//if (angle >= 90) *ptrCCR = degPos90CCR;
		//else if (IsInRange(angle, 45, 90)) *ptrCCR = mapToFloat_t(angle, 45, 90, degPos45CCR, degPos90CCR);
		//else if (IsInRange(angle, 0, 45)) *ptrCCR = mapToFloat_t(angle, 0, 45, degPos45CCR, degPos90CCR);
		//else if (IsInRange(angle, -45, 0)) *ptrCCR = mapToFloat_t(angle, -45, 0, degPos45CCR, degPos90CCR);
		//else if (IsInRange(angle, -90, -45)) *ptrCCR = mapToFloat_t(angle, -90, -45, degPos45CCR, degPos90CCR);
		//else if (angle <= -90) *ptrCCR = degNeg90CCR;
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
 Jak utworzy� definicj� wska�nika na funkcj�?
 Mamy deklaracj� funkcji:
 int mojaFunkcja( float a, int b, const char * c );
 Oczyszczamy j� z nazw argument�w:
 int mojaFunkcja( float, int, const char * );
 Nazw� funkcji zmieniamy na jak�� now� nazw� i dopisujemy na pocz�tku typedef:
 typedef int nazwaTypuT( float, int, const char * );
 Nazw� typu umieszczamy w nawiasach zaokr�glonych:
 typedef int( nazwaTypuT )( float, int, const char * );
 Przed nazw� typu i jednocze�nie za wstawionym nawiasem otwieraj�cym, dostawionym w poprzednim kroku - umieszczamy gwiazdk�:
 typedef int( * nazwaTypuT )( float, int, const char * );
 Jak zapisa� adres funkcji do wska�nika?
 nazwaTypuT pWskaznikNaFunkcje = mojaFunkcja;

 Jak wywo�a� funkcj� zapisan� we wska�niku?
 int iWynik = pWskaznikNaFunkcje( 123.4f, 567, "Koniec" );
 */
