#ifndef SYSTEM_TASK_H_
#define SYSTEM_TASK_H_

#include "common.h"

#define THREAD_NUM 8

// LED线程
#define LED_Thread_StackSize 300 // 线程堆栈大小
#define LED_Thread_Priority 8     // 线程优先级
#define LED_Thread_Tick 20        // 线程时间

// BUZZER线程
#define BUZZER_Thread_StackSize 300 // 线程堆栈大小
#define BUZZER_Thread_Priority 8     // 线程优先级
#define BUZZER_Thread_Tick 20        // 线程时间

// W25QXX线程
#define W25QXX_Thread_StackSize 1000 // 线程堆栈大小
#define W25QXX_Thread_Priority 3     // 线程优先级
#define W25QXX_Thread_Tick 20        // 线程时间

// UART线程
#define UART_Thread_StackSize 1000 // 线程堆栈大小
#define UART_Thread_Priority 3     // 线程优先级
#define UART_Thread_Tick 20        // 线程时间

// SDIO线程
#define SDIO_Thread_StackSize 1000 // 线程堆栈大小
#define SDIO_Thread_Priority 3     // 线程优先级
#define SDIO_Thread_Tick 20        // 线程时间

// USB线程
#define USB_Thread_StackSize 1000 // 线程堆栈大小
#define USB_Thread_Priority 3     // 线程优先级
#define USB_Thread_Tick 20        // 线程时间

// LCD线程
#define LCD_Thread_StackSize 5000 // 线程堆栈大小
#define LCD_Thread_Priority 2     // 线程优先级
#define LCD_Thread_Tick 20        // 线程时间

// WDOG线程
#define WDOG_Thread_StackSize 1000 // 线程堆栈大小
#define WDOG_Thread_Priority 2     // 线程优先级
#define WDOG_Thread_Tick 20        // 线程时间

void LED_task(void * p);
void BUZZER_task(void * p);
void W25QXX_task(void * p);
void UART_task(void * p);
void SDIO_task(void * p);
void USB_task(void * p);
void LCD_task(void * p);
void WDOG_task(void * p);

#endif /* SYSTEM_TASK_H_ */
