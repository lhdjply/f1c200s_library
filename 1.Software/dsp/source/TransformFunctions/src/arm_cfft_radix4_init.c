#include "../inc/transformfunctions.h"

arm_status arm_cfft_radix4_init_q15(
  arm_cfft_radix4_instance_q15 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag)
{
  arm_status status = ARM_MATH_ARGUMENT_ERROR;

  status = ARM_MATH_SUCCESS;
  S->fftLen = fftLen;
  S->pTwiddle = (q15_t *)twiddleCoef_4096_q15;
  S->ifftFlag = ifftFlag;
  S->bitReverseFlag = bitReverseFlag;
  switch(S->fftLen)
  {
    case 4096U:
      S->twidCoefModifier = 1U;
      S->bitRevFactor = 1U;
      S->pBitRevTable = (uint16_t *)armBitRevTable;
      break;
    case 1024U:
      S->twidCoefModifier = 4U;
      S->bitRevFactor = 4U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[3];
      break;
    case 256U:
      S->twidCoefModifier = 16U;
      S->bitRevFactor = 16U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[15];
      break;
    case 64U:
      S->twidCoefModifier = 64U;
      S->bitRevFactor = 64U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[63];
      break;
    case 16U:
      S->twidCoefModifier = 256U;
      S->bitRevFactor = 256U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[255];
      break;
    default:
      status = ARM_MATH_ARGUMENT_ERROR;
      break;
  }
  return status;
}

arm_status arm_cfft_radix4_init_q31(
  arm_cfft_radix4_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag)
{
  arm_status status = ARM_MATH_ARGUMENT_ERROR;

  status = ARM_MATH_SUCCESS;
  S->fftLen = fftLen;
  S->pTwiddle = (q31_t *)twiddleCoef_4096_q31;
  S->ifftFlag = ifftFlag;
  S->bitReverseFlag = bitReverseFlag;

  switch(S->fftLen)
  {
    case 4096U:
      S->twidCoefModifier = 1U;
      S->bitRevFactor = 1U;
      S->pBitRevTable = (uint16_t *)armBitRevTable;
      break;
    case 1024U:
      S->twidCoefModifier = 4U;
      S->bitRevFactor = 4U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[3];
      break;
    case 256U:
      S->twidCoefModifier = 16U;
      S->bitRevFactor = 16U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[15];
      break;
    case 64U:
      S->twidCoefModifier = 64U;
      S->bitRevFactor = 64U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[63];
      break;
    case 16U:
      S->twidCoefModifier = 256U;
      S->bitRevFactor = 256U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[255];
      break;
    default:
      status = ARM_MATH_ARGUMENT_ERROR;
      break;
  }
  return status;
}

arm_status arm_cfft_radix4_init_f32(
  arm_cfft_radix4_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag)
{
  arm_status status = ARM_MATH_ARGUMENT_ERROR;

  status = ARM_MATH_SUCCESS;
  S->fftLen = fftLen;
  S->pTwiddle = (float32_t *)twiddleCoef;
  S->ifftFlag = ifftFlag;
  S->bitReverseFlag = bitReverseFlag;

  switch(S->fftLen)
  {
    case 4096U:
      S->twidCoefModifier = 1U;
      S->bitRevFactor = 1U;
      S->pBitRevTable = (uint16_t *)armBitRevTable;
      S->onebyfftLen = 0.000244140625;
      break;
    case 1024U:
      S->twidCoefModifier = 4U;
      S->bitRevFactor = 4U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[3];
      S->onebyfftLen = 0.0009765625f;
      break;
    case 256U:
      S->twidCoefModifier = 16U;
      S->bitRevFactor = 16U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[15];
      S->onebyfftLen = 0.00390625f;
      break;
    case 64U:
      S->twidCoefModifier = 64U;
      S->bitRevFactor = 64U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[63];
      S->onebyfftLen = 0.015625f;
      break;
    case 16U:
      S->twidCoefModifier = 256U;
      S->bitRevFactor = 256U;
      S->pBitRevTable = (uint16_t *)&armBitRevTable[255];
      S->onebyfftLen = 0.0625f;
      break;
    default:
      status = ARM_MATH_ARGUMENT_ERROR;
      break;
  }
  return status;
}
