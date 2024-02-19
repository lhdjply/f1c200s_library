#ifndef _ARM_MEAN_H
#define _ARM_MEAN_H

#include "arm_math.h"

void arm_mean_q7(const q7_t * pSrc, uint32_t blockSize, q7_t * pResult);
void arm_mean_q15(const q15_t * pSrc, uint32_t blockSize, q15_t * pResult);
void arm_mean_q31(const q31_t * pSrc, uint32_t blockSize, q31_t * pResult);
void arm_mean_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult);

#endif
