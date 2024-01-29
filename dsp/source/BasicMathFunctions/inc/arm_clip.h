#ifndef _ARM_CLIP_H
#define _ARM_CLIP_H

#include "arm_math.h"

void arm_clip_q7(const q7_t * pSrc,
                 q7_t * pDst,
                 q7_t low,
                 q7_t high,
                 uint32_t numSamples);
void arm_clip_q15(const q15_t * pSrc,
                  q15_t * pDst,
                  q15_t low,
                  q15_t high,
                  uint32_t numSamples);
void arm_clip_q31(const q31_t * pSrc,
                  q31_t * pDst,
                  q31_t low,
                  q31_t high,
                  uint32_t numSamples);
void arm_clip_f32(const float32_t * pSrc,
                  float32_t * pDst,
                  float32_t low,
                  float32_t high,
                  uint32_t numSamples);

#endif
