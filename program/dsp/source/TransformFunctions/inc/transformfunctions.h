#ifndef transformfunctions__H
#define transformfunctions__H

#include "arm_math.h"

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const q15_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
} arm_cfft_radix2_instance_q15;

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const q15_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
} arm_cfft_radix4_instance_q15;

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const q31_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
} arm_cfft_radix2_instance_q31;

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const q31_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
} arm_cfft_radix4_instance_q31;

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const float32_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
  float32_t onebyfftLen;
} arm_cfft_radix2_instance_f32;

typedef struct
{
  uint16_t fftLen;
  uint8_t ifftFlag;
  uint8_t bitReverseFlag;
  const float32_t * pTwiddle;
  const uint16_t * pBitRevTable;
  uint16_t twidCoefModifier;
  uint16_t bitRevFactor;
  float32_t onebyfftLen;
} arm_cfft_radix4_instance_f32;

#include "arm_cfft_radix4_init.h"
#include "arm_cfft_radix4.h"

#endif
