#ifndef __CommonTables__H
#define __CommonTables__H

#include "arm_math.h"

extern const q15_t sqrt_initial_lut_q15[];
extern const q31_t sqrt_initial_lut_q31[];
extern const uint16_t armBitRevTable[];
extern const q15_t twiddleCoef_4096_q15[];
extern const q31_t twiddleCoef_4096_q31[];
extern const float32_t twiddleCoef_4096[];
#define twiddleCoef twiddleCoef_4096

#endif
