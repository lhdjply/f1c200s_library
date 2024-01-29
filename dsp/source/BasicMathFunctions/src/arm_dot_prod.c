#include "../inc/basicmathfunctions.h"

void arm_dot_prod_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  uint32_t blockSize,
  q31_t * result)
{
  uint32_t blkCnt;
  q31_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    sum += (q31_t)((q15_t) * pSrcA++ * *pSrcB++);
    blkCnt--;
  }
  *result = sum;
}

void arm_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  uint32_t blockSize,
  q63_t * result)
{
  uint32_t blkCnt;
  q63_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    sum += (q63_t)((q31_t) * pSrcA++ * *pSrcB++);
    blkCnt--;
  }
  *result = sum;
}

void arm_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  uint32_t blockSize,
  q63_t * result)
{
  uint32_t blkCnt;
  q63_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    sum += ((q63_t) * pSrcA++ * *pSrcB++) >> 14U;
    blkCnt--;
  }
  *result = sum;
}

void arm_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  uint32_t blockSize,
  float32_t * result)
{
  uint32_t blkCnt;
  float32_t sum = 0.0f;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    sum += (*pSrcA++) * (*pSrcB++);
    blkCnt--;
  }
  *result = sum;
}
