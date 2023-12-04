#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */
#define RT_NAME_MAX 16
#define RT_ALIGN_SIZE 4
//#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 10
#define RT_TICK_PER_SECOND 1000
//#define RT_USING_OVERFLOW_CHECK
// #define RT_USING_HOOK
// #define RT_HOOK_USING_FUNC_PTR
//#define RT_USING_IDLE_HOOK
//#define RT_IDLE_HOOK_LIST_SIZE 4
//#define IDLE_THREAD_STACK_SIZE 256
//#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512
#define RT_USING_LIBC
#define RT_USING_CACHE

/* Inter-Thread communication */
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
// #define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */
//#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP

/* RT-Thread Components */
#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 256
#define RT_MAIN_THREAD_PRIORITY 3


#endif
