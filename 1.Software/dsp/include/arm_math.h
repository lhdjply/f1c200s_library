#ifndef _ARM_MATH_H
#define _ARM_MATH_H

#include "stdint.h"
#include "math.h"

typedef int8_t q7_t;
typedef int16_t q15_t;
typedef int32_t q31_t;
typedef int64_t q63_t;
typedef float float32_t;
typedef double float64_t;

typedef enum
{
  ARM_MATH_SUCCESS = 0,               /**< No error */
  ARM_MATH_ARGUMENT_ERROR = -1,       /**< One or more arguments are incorrect */
  ARM_MATH_LENGTH_ERROR = -2,         /**< Length of data buffer is incorrect */
  ARM_MATH_SIZE_MISMATCH = -3,        /**< Size of matrices is not compatible with the operation */
  ARM_MATH_NANINF = -4,               /**< Not-a-number (NaN) or infinity is generated */
  ARM_MATH_SINGULAR = -5,             /**< Input matrix is singular and cannot be inverted */
  ARM_MATH_TEST_FAILURE = -6,         /**< Test Failed */
  ARM_MATH_DECOMPOSITION_FAILURE = -7 /**< Decomposition Failed */
} arm_status;

static inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max;
    if(val > max)
    {
      return max;
    }
    else if(val < min)
    {
      return min;
    }
  }
  return val;
}

static inline q31_t clip_q63_to_q31(
  q63_t x)
{
  return ((q31_t)(x >> 32) != ((q31_t)x >> 31)) ? ((0x7FFFFFFF ^ ((q31_t)(x >> 63)))) : (q31_t)x;
}

static inline uint8_t __CLZ(uint32_t value)
{
  if(value == 0)
  {
    return 32U;
  }
  return __builtin_clz(value);
}

static inline uint32_t __QADD8(uint32_t x, uint32_t y)
{
  q31_t r, s, t, u;

  r = __SSAT(((((q31_t)x << 24) >> 24) + (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
  s = __SSAT(((((q31_t)x << 16) >> 24) + (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
  t = __SSAT(((((q31_t)x <<  8) >> 24) + (((q31_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
  u = __SSAT(((((q31_t)x) >> 24) + (((q31_t)y) >> 24)), 8) & (int32_t)0x000000FF;

  return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

static inline uint32_t __QADD16(uint32_t x, uint32_t y)
{
  q31_t r = 0, s = 0;

  r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
  s = __SSAT(((((q31_t)x) >> 16) + (((q31_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

  return ((uint32_t)((s << 16) | (r)));
}

static inline int32_t __QADD(int32_t x, int32_t y)
{
  return ((int32_t)(clip_q63_to_q31((q63_t)x + (q31_t)y)));
}

static inline uint32_t __QSUB8(uint32_t x, uint32_t y)
{
  q31_t r, s, t, u;

  r = __SSAT(((((q31_t)x << 24) >> 24) - (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
  s = __SSAT(((((q31_t)x << 16) >> 24) - (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
  t = __SSAT(((((q31_t)x <<  8) >> 24) - (((q31_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
  u = __SSAT(((((q31_t)x) >> 24) - (((q31_t)y) >> 24)), 8) & (int32_t)0x000000FF;

  return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

static inline uint32_t __QSUB16(uint32_t x, uint32_t y)
{
  q31_t r, s;

  r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
  s = __SSAT(((((q31_t)x) >> 16) - (((q31_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

  return ((uint32_t)((s << 16) | (r)));
}

static inline int32_t __QSUB(int32_t x, int32_t y)
{
  return ((int32_t)(clip_q63_to_q31((q63_t)x - (q31_t)y)));
}

#include "../source/BasicMathFunctions/inc/basicmathfunctions.h"
#include "../source/CommonTables/inc/commontables.h"
#include "../source/ComplexMathFunctions/inc/complexmathfunctions.h"
#include "../source/FastMathFunctions/inc/fastmathfunctions.h"
#include "../source/StatisticsFunctions/inc/statisticsfunctions.h"
#include "../source/SupportFunctions/inc/supportfunctions.h"
#include "../source/TransformFunctions/inc/transformfunctions.h"

#endif
