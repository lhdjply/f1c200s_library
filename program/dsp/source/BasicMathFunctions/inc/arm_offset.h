#ifndef _ARM_OFFSET_H
#define _ARM_OFFSET_H

#include "arm_math.h"

void arm_offset_q7(
  const q7_t * pSrc,
  q7_t offset,
  q7_t * pDst,
  uint32_t blockSize);
void arm_offset_q15(
  const q15_t * pSrc,
  q15_t offset,
  q15_t * pDst,
  uint32_t blockSize);
void arm_offset_q31(
  const q31_t * pSrc,
  q31_t offset,
  q31_t * pDst,
  uint32_t blockSize);
void arm_offset_f32(
  const float32_t * pSrc,
  float32_t offset,
  float32_t * pDst,
  uint32_t blockSize);

#endif
