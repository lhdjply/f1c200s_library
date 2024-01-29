#ifndef _ARM_MULT_H
#define _ARM_MULT_H

#include "arm_math.h"

void arm_mult_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);
void arm_mult_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);
void arm_mult_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);
void arm_mult_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

#endif
