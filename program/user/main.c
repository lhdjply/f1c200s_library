#include <task.h>

rt_thread_t thread[THREAD_NUM];

int main(void)
{
  thread[0] = rt_thread_create("BUZZER",
                               BUZZER_task,
                               RT_NULL,
                               BUZZER_Thread_StackSize,
                               BUZZER_Thread_Priority,
                               BUZZER_Thread_Tick);
  rt_thread_startup(thread[0]);

  thread[1] = rt_thread_create("UART",
                               UART_task,
                               RT_NULL,
                               UART_Thread_StackSize,
                               UART_Thread_Priority,
                               UART_Thread_Tick);
  rt_thread_startup(thread[1]);

  thread[2] = rt_thread_create("LCD",
                               LCD_task,
                               RT_NULL,
                               LCD_Thread_StackSize,
                               LCD_Thread_Priority,
                               LCD_Thread_Tick);
  rt_thread_startup(thread[2]);

  thread[3] = rt_thread_create("WDOG",
                               WDOG_task,
                               RT_NULL,
                               WDOG_Thread_StackSize,
                               WDOG_Thread_Priority,
                               WDOG_Thread_Tick);
  rt_thread_startup(thread[3]);
}
