#include "../inc/transformfunctions.h"

void arm_bitreversal_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab)
{
  q31_t * pSrc = (q31_t *)pSrc16;
  q31_t in;
  uint32_t fftLenBy2, fftLenBy2p1;
  uint32_t i, j;

  j = 0U;
  fftLenBy2 = fftLen / 2U;
  fftLenBy2p1 = (fftLen / 2U) + 1U;

  for(i = 0U; i <= (fftLenBy2 - 2U); i += 2U)
  {
    if(i < j)
    {
      in = pSrc[i];
      pSrc[i] = pSrc[j];
      pSrc[j] = in;

      in = pSrc[i + fftLenBy2p1];
      pSrc[i + fftLenBy2p1] = pSrc[j + fftLenBy2p1];
      pSrc[j + fftLenBy2p1] = in;
    }

    in = pSrc[i + 1U];
    pSrc[i + 1U] = pSrc[j + fftLenBy2];
    pSrc[j + fftLenBy2] = in;

    j = *pBitRevTab;

    pBitRevTab += bitRevFactor;
  }
}

void arm_bitreversal_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab)
{
  uint32_t fftLenBy2, fftLenBy2p1, i, j;
  q31_t in;

  j = 0U;
  fftLenBy2 = fftLen / 2U;
  fftLenBy2p1 = (fftLen / 2U) + 1U;

  for(i = 0U; i <= (fftLenBy2 - 2U); i += 2U)
  {
    if(i < j)
    {
      in = pSrc[2U * i];
      pSrc[2U * i] = pSrc[2U * j];
      pSrc[2U * j] = in;

      in = pSrc[(2U * i) + 1U];
      pSrc[(2U * i) + 1U] = pSrc[(2U * j) + 1U];
      pSrc[(2U * j) + 1U] = in;

      in = pSrc[2U * (i + fftLenBy2p1)];
      pSrc[2U * (i + fftLenBy2p1)] = pSrc[2U * (j + fftLenBy2p1)];
      pSrc[2U * (j + fftLenBy2p1)] = in;

      in = pSrc[(2U * (i + fftLenBy2p1)) + 1U];
      pSrc[(2U * (i + fftLenBy2p1)) + 1U] =
        pSrc[(2U * (j + fftLenBy2p1)) + 1U];
      pSrc[(2U * (j + fftLenBy2p1)) + 1U] = in;
    }

    in = pSrc[2U * (i + 1U)];
    pSrc[2U * (i + 1U)] = pSrc[2U * (j + fftLenBy2)];
    pSrc[2U * (j + fftLenBy2)] = in;

    in = pSrc[(2U * (i + 1U)) + 1U];
    pSrc[(2U * (i + 1U)) + 1U] = pSrc[(2U * (j + fftLenBy2)) + 1U];
    pSrc[(2U * (j + fftLenBy2)) + 1U] = in;

    j = *pBitRevTab;

    pBitRevTab += bitRevFactor;
  }
}

void arm_bitreversal_f32(
  float32_t * pSrc,
  uint16_t fftSize,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab)
{
  uint16_t fftLenBy2, fftLenBy2p1;
  uint16_t i, j;
  float32_t in;

  j = 0U;
  fftLenBy2 = fftSize >> 1U;
  fftLenBy2p1 = (fftSize >> 1U) + 1U;

  for(i = 0U; i <= (fftLenBy2 - 2U); i += 2U)
  {
    if(i < j)
    {
      in = pSrc[2U * i];
      pSrc[2U * i] = pSrc[2U * j];
      pSrc[2U * j] = in;

      in = pSrc[(2U * i) + 1U];
      pSrc[(2U * i) + 1U] = pSrc[(2U * j) + 1U];
      pSrc[(2U * j) + 1U] = in;

      in = pSrc[2U * (i + fftLenBy2p1)];
      pSrc[2U * (i + fftLenBy2p1)] = pSrc[2U * (j + fftLenBy2p1)];
      pSrc[2U * (j + fftLenBy2p1)] = in;

      in = pSrc[(2U * (i + fftLenBy2p1)) + 1U];
      pSrc[(2U * (i + fftLenBy2p1)) + 1U] =
        pSrc[(2U * (j + fftLenBy2p1)) + 1U];
      pSrc[(2U * (j + fftLenBy2p1)) + 1U] = in;
    }
    in = pSrc[2U * (i + 1U)];
    pSrc[2U * (i + 1U)] = pSrc[2U * (j + fftLenBy2)];
    pSrc[2U * (j + fftLenBy2)] = in;

    in = pSrc[(2U * (i + 1U)) + 1U];
    pSrc[(2U * (i + 1U)) + 1U] = pSrc[(2U * (j + fftLenBy2)) + 1U];
    pSrc[(2U * (j + fftLenBy2)) + 1U] = in;

    j = *pBitRevTab;

    pBitRevTab += bitRevFactor;
  }
}
