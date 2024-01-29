#ifndef _ARM_DOT_PROD_H
#define _ARM_DOT_PROD_H

#include "arm_math.h"

void arm_dot_prod_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  uint32_t blockSize,
  q31_t * result);
void arm_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);
void arm_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);
void arm_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  uint32_t blockSize,
  float32_t * result);

#endif
