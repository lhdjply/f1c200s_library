#ifndef _ARM_CMPLX_MAG_H
#define _ARM_CMPLX_MAG_H

#include "arm_math.h"

void arm_cmplx_mag_q15(
  const q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);
void arm_cmplx_mag_q31(
  const q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);
void arm_cmplx_mag_f32(
  const float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);
void arm_cmplx_mag_f64(
  const float64_t * pSrc,
  float64_t * pDst,
  uint32_t numSamples);

#endif
