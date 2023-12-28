#ifndef _ARM_POWER_H
#define _ARM_POWER_H

#include "arm_math.h"

void arm_power_q7(const q7_t * pSrc, uint32_t blockSize, q31_t * pResult);
void arm_power_q15(const q15_t * pSrc, uint32_t blockSize, q63_t * pResult);
void arm_power_q31(const q31_t * pSrc, uint32_t blockSize, q63_t * pResult);
void arm_power_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult);
#endif
