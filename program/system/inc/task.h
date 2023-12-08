#ifndef SYSTEM_TASK_H_
#define SYSTEM_TASK_H_

#include "common.h"

#define THREAD_NUM 3

// BUZZER线程
#define BUZZER_Thread_StackSize 1000 // 线程堆栈大小
#define BUZZER_Thread_Priority 8     // 线程优先级
#define BUZZER_Thread_Tick 20        // 线程时间

// LCD线程
#define LCD_Thread_StackSize 5000 // 线程堆栈大小
#define LCD_Thread_Priority 2     // 线程优先级
#define LCD_Thread_Tick 20        // 线程时间

void BUZZER_task(void * p);
void LCD_task(void * p);

#endif /* SYSTEM_TASK_H_ */
