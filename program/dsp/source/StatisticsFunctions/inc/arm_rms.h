#ifndef _ARM_RMS_H
#define _ARM_RMS_H

#include "arm_math.h"

void arm_rms_q15(const q15_t * pSrc, uint32_t blockSize, q15_t * pResult);
void arm_rms_q31(const q31_t * pSrc, uint32_t blockSize, q31_t * pResult);
void arm_rms_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult);

#endif
