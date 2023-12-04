#include "uart.h"
#include "interrupt.h"
#include "common.h"

UART_DATA uart_Data;

static void MY_UART_IRQHandler(int irqno, void * param);
static void UART_IDLE_task(void * p);

void MY_UART_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  UART_InitTypeDef UART_InitStructure;

  GPIO_AF_Remap(GPIOA, GPIO_PinSource2, GPIO_AF_PA2_UART1_RX);
  GPIO_AF_Remap(GPIOA, GPIO_PinSource3, GPIO_AF_PA3_UART1_TX);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_UART1, ENABLE);
  CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_UART1, ENABLE);

  UART_InitStructure.UART_BaudRate = 115200;
  UART_InitStructure.UART_WordLength = UART_WordLength_8b;
  UART_InitStructure.UART_StopBits = UART_StopBits_1;
  UART_InitStructure.UART_Parity = UART_Parity_No;
  UART_Init(MY_UART, &UART_InitStructure);

  UART_ITConfig(MY_UART, UART_IT_ERBFI, ENABLE);

  rt_hw_interrupt_install(UART1_INTERRUPT, MY_UART_IRQHandler, NULL, "uart_irq");
  rt_hw_interrupt_umask(UART1_INTERRUPT);

  uart_Data.sem = rt_sem_create("uart_sem", 0, RT_IPC_FLAG_FIFO);
  uart_Data.mutex = rt_mutex_create("uart_mutex", RT_IPC_FLAG_FIFO);

  rt_thread_t uart_idle = rt_thread_create("uart_idle",
                                           UART_IDLE_task,
                                           NULL,
                                           300,
                                           2,
                                           20);
  rt_thread_startup(uart_idle);
}

static void uart_idle(UART_DATA * uart_data)
{
  if(uart_data->flag == 1)
  {
    uart_data->time++;
    if(uart_data->time >= 5)
    {
      uart_data->flag = 0;
      uart_data->time = 0;
      uart_data->len = uart_data->count;
      uart_data->count = 0;
      rt_sem_release(uart_data->sem);
    }
  }
}

static void UART_IDLE_task(void * p)
{
  while(1)
  {
    uart_idle(&uart_Data);
    rt_thread_mdelay(1);
  }
}

static void MY_UART_IRQHandler(int irqno, void * param)
{
  uint8_t temp;
  rt_interrupt_enter();
  if(UART_Get_IIR_FLAG(MY_UART, UART_IIR_RXNE) == SET)
  {
    temp = UART_ReceiveData(MY_UART);
    uart_Data.RXD_BUF[uart_Data.count] = temp;
    uart_Data.count++;
    uart_Data.flag = 1;
    uart_Data.time = 0;
  }
  rt_interrupt_leave();
}
