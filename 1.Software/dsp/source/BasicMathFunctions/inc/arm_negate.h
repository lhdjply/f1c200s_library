#ifndef _ARM_NEGATE_H
#define _ARM_NEGATE_H

#include "arm_math.h"

void arm_negate_q7(const q7_t * pSrc, q7_t * pDst, uint32_t blockSize);
void arm_negate_q15(const q15_t * pSrc, q15_t * pDst, uint32_t blockSize);
void arm_negate_q31(const q31_t * pSrc, q31_t * pDst, uint32_t blockSize);
void arm_negate_f32(const float32_t * pSrc, float32_t * pDst, uint32_t blockSize);

#endif
