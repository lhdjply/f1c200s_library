#include <task.h>

rt_thread_t thread[THREAD_NUM];

int main(void)
{
  thread[0] = rt_thread_create("BELL",
                               BELL_task,
                               RT_NULL,
                               BELL_Thread_StackSize,
                               BELL_Thread_Priority,
                               BELL_Thread_Tick);
  rt_thread_startup(thread[0]);

  thread[2] = rt_thread_create("LCD",
                               LCD_task,
                               RT_NULL,
                               LCD_Thread_StackSize,
                               LCD_Thread_Priority,
                               LCD_Thread_Tick);
  rt_thread_startup(thread[2]);
}
