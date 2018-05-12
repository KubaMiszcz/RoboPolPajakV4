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

///dasdsa
///@param
static long mapToLong(long x, long fromLow, long fromHigh, long toLow, long toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

static float mapToFloat(float x, float fromLow, float fromHigh, float toLow, float toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

static uint16_t mapAngleToCCR(int8_t x, int8_t fromLow, int8_t fromHigh, uint16_t toLow, uint16_t toHigh)
{
	return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
};

