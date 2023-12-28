#include "../inc/fastmathfunctions.h"

#define Q12QUARTER 0x2000
#define Q28QUARTER 0x20000000

arm_status arm_sqrt_q15(q15_t in, q15_t * pOut)
{
  q15_t number, var1, signBits1, temp;
  number = in;

  if(number > 0)
  {
    signBits1 = __CLZ(number) - 17;

    if((signBits1 % 2) == 0)
    {
      number = number << signBits1;
    }
    else
    {
      number = number << (signBits1 - 1);
    }
    var1 = sqrt_initial_lut_q15[(number >> 11) - (Q12QUARTER >> 11)];

    temp = ((q31_t)var1 * var1) >> 12;
    temp = ((q31_t)number * temp) >> 15;
    temp = 0x3000 - temp;
    var1 = ((q31_t)var1 * temp) >> 13;

    temp = ((q31_t)var1 * var1) >> 12;
    temp = ((q31_t)number * temp) >> 15;
    temp = 0x3000 - temp;
    var1 = ((q31_t)var1 * temp) >> 13;

    temp = ((q31_t)var1 * var1) >> 12;
    temp = ((q31_t)number * temp) >> 15;
    temp = 0x3000 - temp;
    var1 = ((q31_t)var1 * temp) >> 13;

    var1 = ((q15_t)(((q31_t)number * var1) >> 12));

    if((signBits1 % 2) == 0)
    {
      var1 = var1 >> (signBits1 / 2);
    }
    else
    {
      var1 = var1 >> ((signBits1 - 1) / 2);
    }
    *pOut = var1;

    return ARM_MATH_SUCCESS;
  }
  else
  {
    *pOut = 0;
    return ARM_MATH_ARGUMENT_ERROR;
  }
}

arm_status arm_sqrt_q31(q31_t in, q31_t * pOut)
{
  q31_t number, var1, signBits1, temp;

  number = in;

  if(number > 0)
  {
    signBits1 = __CLZ(number) - 1;

    if((signBits1 % 2) == 0)
    {
      number = number << signBits1;
    }
    else
    {
      number = number << (signBits1 - 1);
    }

    var1 = sqrt_initial_lut_q31[(number >> 26) - (Q28QUARTER >> 26)];

    temp = ((q63_t)var1 * var1) >> 28;
    temp = ((q63_t)number * temp) >> 31;
    temp = 0x30000000 - temp;
    var1 = ((q63_t)var1 * temp) >> 29;

    temp = ((q63_t)var1 * var1) >> 28;
    temp = ((q63_t)number * temp) >> 31;
    temp = 0x30000000 - temp;
    var1 = ((q63_t)var1 * temp) >> 29;

    temp = ((q63_t)var1 * var1) >> 28;
    temp = ((q63_t)number * temp) >> 31;
    temp = 0x30000000 - temp;
    var1 = ((q63_t)var1 * temp) >> 29;

    var1 = ((q31_t)(((q63_t)number * var1) >> 28));

    if((signBits1 % 2) == 0)
    {
      var1 = var1 >> (signBits1 / 2);
    }
    else
    {
      var1 = var1 >> ((signBits1 - 1) / 2);
    }
    *pOut = var1;

    return ARM_MATH_SUCCESS;
  }
  else
  {
    *pOut = 0;

    return ARM_MATH_ARGUMENT_ERROR;
  }
}

arm_status arm_sqrt_f32(const float32_t in, float32_t * pOut)
{
  if(in >= 0.0f)
  {
    *pOut = sqrtf(in);
    return ARM_MATH_SUCCESS;
  }
  else
  {
    *pOut = 0.0f;
    return ARM_MATH_ARGUMENT_ERROR;
  }
}
