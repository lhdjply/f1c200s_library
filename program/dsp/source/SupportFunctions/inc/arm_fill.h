#ifndef _ARM_FILL_H
#define _ARM_FILL_H

#include "arm_math.h"

void arm_fill_q7(q7_t value, q7_t * pDst, uint32_t blockSize);
void arm_fill_q15(q15_t value, q15_t * pDst, uint32_t blockSize);
void arm_fill_q31(q31_t value, q31_t * pDst, uint32_t blockSize);
void arm_fill_f32(float32_t value, float32_t * pDst, uint32_t blockSize);

#endif
