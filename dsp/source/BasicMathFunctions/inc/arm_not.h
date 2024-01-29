#ifndef _ARM_NOT_H
#define _ARM_NOT_H

#include "arm_math.h"

void arm_not_u8(
  const uint8_t * pSrc,
  uint8_t * pDst,
  uint32_t blockSize);
void arm_not_u16(
  const uint16_t * pSrc,
  uint16_t * pDst,
  uint32_t blockSize);
void arm_not_u32(
  const uint32_t * pSrc,
  uint32_t * pDst,
  uint32_t blockSize);

#endif
