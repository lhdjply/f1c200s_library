#include "../inc/basicmathfunctions.h"

void arm_mult_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q7_t) __SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
    blkCnt--;
  }
}

void arm_mult_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q15_t) __SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
    blkCnt--;
  }
}

void arm_mult_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  q31_t out;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    out = ((q63_t) * pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;
    blkCnt--;
  }
}

void arm_mult_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrcA++) * (*pSrcB++);
    blkCnt--;
  }
}
