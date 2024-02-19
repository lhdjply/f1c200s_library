#ifndef _ARM_OR_H
#define _ARM_OR_H

#include "arm_math.h"

void arm_or_u8(
  const uint8_t * pSrcA,
  const uint8_t * pSrcB,
  uint8_t * pDst,
  uint32_t blockSize);
void arm_or_u16(
  const uint16_t * pSrcA,
  const uint16_t * pSrcB,
  uint16_t * pDst,
  uint32_t blockSize);
void arm_or_u32(
  const uint32_t * pSrcA,
  const uint32_t * pSrcB,
  uint32_t * pDst,
  uint32_t blockSize);

#endif
