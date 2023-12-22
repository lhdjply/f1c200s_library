#ifndef _ARM_MIN_H
#define _ARM_MIN_H

#include "arm_math.h"

void arm_min_q7(const q7_t * pSrc, uint32_t blockSize, q7_t * pResult, uint32_t * pIndex);
void arm_min_q15(const q15_t * pSrc, uint32_t blockSize, q15_t * pResult, uint32_t * pIndex);
void arm_min_q31(const q31_t * pSrc, uint32_t blockSize, q31_t * pResult, uint32_t * pIndex);
void arm_min_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult, uint32_t * pIndex);

#endif
