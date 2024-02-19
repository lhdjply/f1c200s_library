#include "../inc/basicmathfunctions.h"

void arm_negate_q7(
  const q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  q7_t in;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    in = *pSrc++;
    *pDst++ = (in == (q7_t) 0x80) ? (q7_t) 0x7f : -in;
    blkCnt--;
  }
}

void arm_negate_q15(
  const q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  q15_t in;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    in = *pSrc++;
    *pDst++ = (in == (q15_t) 0x8000) ? (q15_t) 0x7fff : -in;
    blkCnt--;
  }
}

void arm_negate_q31(
  const q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  q31_t in;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    in = *pSrc++;
    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
    blkCnt--;
  }
}

void arm_negate_f32(
  const float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = -*pSrc++;
    blkCnt--;
  }
}
