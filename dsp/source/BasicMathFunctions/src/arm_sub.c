#include "../inc/basicmathfunctions.h"

void arm_sub_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q7_t) __SSAT((q15_t) * pSrcA++ - *pSrcB++, 8);
    blkCnt--;
  }
}

void arm_sub_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q15_t) __SSAT(((q31_t) * pSrcA++ - *pSrcB++), 16);
    blkCnt--;
  }
}

void arm_sub_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = __QSUB(*pSrcA++, *pSrcB++);
    blkCnt--;
  }
}

void arm_sub_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrcA++) - (*pSrcB++);
    blkCnt--;
  }
}
