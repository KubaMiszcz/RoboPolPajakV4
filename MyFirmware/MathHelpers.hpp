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

//! ORDER DEFINITIONS HERE IS IMPORTANT

///dasdsa
///@param
static long mapToLong(long x, long fromLow, long fromHigh, long toLow, long toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

static float_t mapToFloat(float_t x, float_t fromLow, float_t fromHigh, float_t toLow, float_t toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

static uint16_t mapAngleToCCR(float_t x, int8_t fromLow, int8_t fromHigh, uint16_t toLow, uint16_t toHigh)
{
	return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

static float_t myAtan2(float_t y, float_t x)
{
	return (float_t)atan2((double)y, (double)x);
}; 

float_t ToDegrees(float_t rad) {
	return rad*TO_DEGREES;
};

static float_t myPowToSecond(int32_t y, int32_t x)
{
	return (float_t)pow((double)y, (double)x);
};


