#ifndef _ARM_SCALE_H
#define _ARM_SCALE_H

#include "arm_math.h"

void arm_scale_q7(
  const q7_t * pSrc,
  q7_t scaleFract,
  int8_t shift,
  q7_t * pDst,
  uint32_t blockSize);
void arm_scale_q15(
  const q15_t * pSrc,
  q15_t scaleFract,
  int8_t shift,
  q15_t * pDst,
  uint32_t blockSize);
void arm_scale_q31(
  const q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize);
void arm_scale_f32(
  const float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize);

#endif
