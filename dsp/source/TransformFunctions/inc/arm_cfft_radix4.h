#ifndef _ARM_CFFT_RADIX4_H
#define _ARM_CFFT_RADIX4_H

#include "arm_math.h"

void arm_cfft_radix4_q15(const arm_cfft_radix4_instance_q15 * S, q15_t * pSrc);
void arm_cfft_radix4_q31(const arm_cfft_radix4_instance_q31 * S, q31_t * pSrc);
void arm_cfft_radix4_f32(const arm_cfft_radix4_instance_f32 * S, float32_t * pSrc);

#endif
