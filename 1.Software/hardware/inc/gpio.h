#ifndef __GPIO_H
#define __GPIO_H

#include "sys.h"

#define LED PEout(5)
#define BUZZER PEout(4)

void LED_Init(void);
void BUZZER_Init(void);

#endif
