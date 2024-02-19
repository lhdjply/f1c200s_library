#include "../inc/statisticsfunctions.h"

void arm_power_q7(
  const q7_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult)
{
  uint32_t blkCnt;
  q31_t sum = 0;
  q7_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += ((q15_t) in * in);
    blkCnt--;
  }
  *pResult = sum;
}

void arm_power_q15(
  const q15_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult)
{
  uint32_t blkCnt;
  q63_t sum = 0;
  q15_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += ((q31_t) in * in);
    blkCnt--;
  }
  *pResult = sum;
}

void arm_power_q31(
  const q31_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult)
{
  uint32_t blkCnt;
  q63_t sum = 0;
  q31_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += ((q63_t) in * in) >> 14U;
    blkCnt--;
  }
  *pResult = sum;
}

void arm_power_f32(
  const float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult)
{
  uint32_t blkCnt;
  float32_t sum = 0.0f;
  float32_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += in * in;
    blkCnt--;
  }
  *pResult = sum;
}
