#ifndef __GPIO_H
#define __GPIO_H

#include "sys.h"

#define BELL PEout(4)
#define KEY PEin(12)

void BELL_Init(void);
void KEY_Init(void);
void BELL_Time(uint16_t time);

#endif
