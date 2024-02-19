/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rthw.h>
#include <rtthread.h>

rt_weak void machine_reset(void)
{
    rt_kprintf("reboot system...\n");
    rt_hw_interrupt_disable();
    while (1);
}

rt_weak void machine_shutdown(void)
{
    rt_kprintf("shutdown...\n");
    rt_hw_interrupt_disable();
    while (1);
}

