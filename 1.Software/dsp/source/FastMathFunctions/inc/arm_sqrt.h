#ifndef _ARM_SQRT_H
#define _ARM_SQRT_H

#include "arm_math.h"

arm_status arm_sqrt_q15(q15_t in, q15_t * pOut);
arm_status arm_sqrt_q31(q31_t in, q31_t * pOut);
arm_status arm_sqrt_f32(float32_t in, float32_t * pOut);

#endif
