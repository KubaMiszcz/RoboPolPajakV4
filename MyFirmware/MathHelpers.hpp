/*
 * MathHelpers.hpp
 *
 *  Created on: May 6, 2018
 *      Author: KubaMiszcz
 */

#pragma once
 /**
   * @brief  Sets .
   *
   * @note   This function uses.
   *
   * @param  G the GPIO peripheral
   * @param  G written.
   * @param  PinState: specifies the value to be written to the selected bit.
   *          Thi
   * @retval None
   */

   //!+ORDER DEFINITIONS HERE IS IMPORTANT
   ///<summary> 
   ///map form one range to another, all data in float_t
///@param x output
   ///</summary>
static float_t mapToFloat(float_t x, float_t fromLow, float_t fromHigh, float_t toLow, float_t toHigh)
{
	return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

float_t ToDegrees(float_t rad) {
	return rad*TO_DEGREES;
};

///<summary> 
///
///</summary>
static bool IsInRange(int32_t val, int32_t min, int32_t max, bool isMinClosed = false, bool isMaxClosed = false)
{
	if (isMinClosed)
	{
		if (isMaxClosed)			return (val <= max && val >= min) ? true : false;
		else 			return (val < max && val >= min) ? true : false;
	}
	else {
		if (isMaxClosed)			return (val <= max && val > min) ? true : false;
		else 			return (val < max && val > min) ? true : false;
	}

};


