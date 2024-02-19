#ifndef _ARM_SHIFT_H
#define _ARM_SHIFT_H

#include "arm_math.h"

void arm_shift_q7(
  const q7_t * pSrc,
  int8_t shiftBits,
  q7_t * pDst,
  uint32_t blockSize);
void arm_shift_q15(
  const q15_t * pSrc,
  int8_t shiftBits,
  q15_t * pDst,
  uint32_t blockSize);
void arm_shift_q31(
  const q31_t * pSrc,
  int8_t shiftBits,
  q31_t * pDst,
  uint32_t blockSize);

#endif
