#include "../inc/statisticsfunctions.h"

void arm_mean_q7(const q7_t * pSrc, uint32_t blockSize, q7_t * pResult)
{
  uint32_t blkCnt;
  q31_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    sum += *pSrc++;
    blkCnt--;
  }
  *pResult = (q7_t)(sum / (int32_t)blockSize);
}

void arm_mean_q15(const q15_t * pSrc, uint32_t blockSize, q15_t * pResult)
{
  uint32_t blkCnt;
  q31_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    sum += *pSrc++;
    blkCnt--;
  }
  *pResult = (q15_t)(sum / (int32_t)blockSize);
}

void arm_mean_q31(const q31_t * pSrc, uint32_t blockSize, q31_t * pResult)
{
  uint32_t blkCnt;
  q63_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    sum += *pSrc++;
    blkCnt--;
  }
  *pResult = (q31_t)(sum / blockSize);
}

void arm_mean_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult)
{
  uint32_t blkCnt;
  float32_t sum = 0;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    sum += *pSrc++;
    blkCnt--;
  }
  *pResult = (sum / blockSize);
}
