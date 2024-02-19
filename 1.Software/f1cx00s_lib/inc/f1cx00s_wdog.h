#ifndef __F1CX00S_WDOG__H
#define __F1CX00S_WDOG__H

#include "f1cx00s.h"

#define WDOG_RST_MODE    (0x01)
#define WDOG_IRQ_MODE    (0x02)

void WDOG_Set_Mode(uint8_t mode);
void WDOG_Feed(void);
void WDOG_Enable(void);
void WDOG_Set_Value(uint8_t value);
uint8_t WDOG_Get_Value(void);

#endif
