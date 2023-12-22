#include "../inc/complexmathfunctions.h"

void arm_cmplx_mag_q15(
  const q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples)
{
  q31_t res;
  uint32_t blkCnt;

  q15_t real, imag;
  q31_t acc0, acc1;

  blkCnt = numSamples;

  while(blkCnt > 0U)
  {
    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31_t)real * real);
    acc1 = ((q31_t)imag * imag);

    arm_sqrt_q31((acc0 + acc1) >> 1, &res);
    *pDst++ = res >> 16;

    blkCnt--;
  }
}

void arm_cmplx_mag_q31(
  const q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples)
{
  uint32_t blkCnt;
  q31_t real, imag;
  q31_t acc0, acc1;

  blkCnt = numSamples;

  while(blkCnt > 0U)
  {
    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31_t)(((q63_t)real * real) >> 33);
    acc1 = (q31_t)(((q63_t)imag * imag) >> 33);

    arm_sqrt_q31(acc0 + acc1, pDst++);

    blkCnt--;
  }
}

void arm_cmplx_mag_f32(
  const float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples)
{
  uint32_t blkCnt;
  float32_t real, imag;

  blkCnt = numSamples;

  while(blkCnt > 0U)
  {
    real = *pSrc++;
    imag = *pSrc++;

    arm_sqrt_f32((real * real) + (imag * imag), pDst++);

    blkCnt--;
  }
}

void arm_cmplx_mag_f64(
  const float64_t * pSrc,
  float64_t * pDst,
  uint32_t numSamples)
{
  uint32_t blkCnt;
  float64_t real, imag;

  blkCnt = numSamples;

  while(blkCnt > 0U)
  {
    real = *pSrc++;
    imag = *pSrc++;

    *pDst++ = sqrt((real * real) + (imag * imag));

    blkCnt--;
  }
}
