#include <rthw.h>
#include <rtthread.h>

#include "interrupt.h"
#include "sys.h"
#include "mmu.h"

static void os_clock_irq_handle(int irqno, void *param)
{
    volatile rt_uint32_t *temp_addr = (rt_uint32_t *)(0x01C20C00 + 0x04);

    /* clear timer */
    *temp_addr |= 0x01;
    rt_tick_increase();
}

static void mmu_init(void)
{
    struct mem_desc r6_mem_desc[] =
        {
            {0x00000000, 0xFFFFFFFF, 0x00000000, RW_NCNB},   /* None cached for 4G memory */
            {0x80000000, 0x84000000 - 1, 0x80000000, RW_CB}, /* 64M cached SDRAM memory */
            //{ 0x00000000, 0x00001000-1, 0x80000000, RW_CB },         /* isr vector table */
            // here not set mmu
            // start_gcc.S Copy vector to the correct address
        };

    rt_hw_mmu_init(r6_mem_desc, sizeof(r6_mem_desc) / sizeof(r6_mem_desc[0]));
}

static void os_clock_init(void)
{
    rt_uint32_t temp;
    volatile rt_uint32_t *temp_addr;

    /* reload value */
    temp = 0xB71B00 / RT_TICK_PER_SECOND;
    temp_addr = (rt_uint32_t *)(0x01C20C00 + 0x14);
    *temp_addr = temp;

    /* continuous | /2 | 24Mhz |  reload*/
    temp = (0x00 << 7) | (0x01 << 4) | (0x01 << 2) | (0x00 << 1);
    temp_addr = (rt_uint32_t *)(0x01C20C00 + 0x10);
    *temp_addr &= 0xffffff00;
    *temp_addr |= temp;

    /* open timer irq */
    temp = 0x01 << 0;
    temp_addr = (rt_uint32_t *)(0x01C20C00);
    *temp_addr |= temp;

    /* set init value */
    temp_addr = (rt_uint32_t *)(0x01C20C00 + 0x18);
    *temp_addr = 0;

    /* begin run timer */
    temp = 0x01 << 0;
    temp_addr = (rt_uint32_t *)(0x01C20C00 + 0x10);
    *temp_addr |= temp;

    temp_addr = (rt_uint32_t *)(0x01C20C00);
    /* set irq handle */
    rt_hw_interrupt_install(TIMER0_INTERRUPT, os_clock_irq_handle, (void *)temp_addr, "timer");
    rt_hw_interrupt_umask(TIMER0_INTERRUPT);
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024 * 1024 * 16 // 16M空间给RTthread
static rt_uint8_t rt_heap[RT_HEAP_SIZE];
rt_weak void *rt_heap_begin_get(void)
{
    return rt_heap;
}

rt_weak void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_hw_board_init(void)
{
    Video_Set_Pll_Clk(198000000);
    CCU_DRAM_ClockCmd(CCU_BE_GATING_DRAM, ENABLE);

    mmu_init();
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

    os_clock_init();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
