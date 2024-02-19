#ifndef SYSTEM_DELAY_H_
#define SYSTEM_DELAY_H_

#include "sys.h"
#include "rtthread.h"

static inline void delay_unit(int loops)
{
  __asm__ __volatile__("1:\n"
                       "subs %0, %1, #1\n"
                       "bne 1b"
                       : "=r"(loops)
                       : "0"(loops));
}

#define delay_us(n) delay_unit(n * 104)
#define delay_ms rt_thread_mdelay

#endif /* SYSTEM_DELAY_H_ */
