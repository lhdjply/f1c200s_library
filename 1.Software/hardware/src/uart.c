#include "uart.h"
#include "interrupt.h"
#include "common.h"

UART_DATA uart_Data;

static void UART1_IRQHandler(int irqno, void * param);
static void UART_IDLE_task(void * p);

void UART1_Init(void)
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
  UART_Init(UART1, &UART_InitStructure);

  UART_ITConfig(UART1, UART_IT_ERBFI, ENABLE);

  rt_hw_interrupt_install(UART1_INTERRUPT, UART1_IRQHandler, NULL, "uart1_irq");
  rt_hw_interrupt_umask(UART1_INTERRUPT);

  rt_thread_t uart_idle = rt_thread_create("uart_idle",
                                           UART_IDLE_task,
                                           NULL,
                                           300,
                                           2,
                                           20);
  rt_thread_startup(uart_idle);
}

void My_Printf(char * format, ...)
{
  uint32_t i;
  va_list p;
  va_start(p, format);
  vsprintf((char *)uart_Data.TXD_BUF, format, p);
  va_end(p);
  for(i = 0; i < strlen((char *)uart_Data.TXD_BUF); i++)
  {
    UART_SendData(UART1, uart_Data.TXD_BUF[i]);
    while(UART_Get_Status(UART1, UART_USR_TFNF) != SET)
    {
    }
  }
}

static void uart_idle(UART_DATA * uart_data)
{
  if(uart_data->receiving_flag == 1)
  {
    uart_data->time++;
    if(uart_data->time >= 5)
    {
      uart_data->receiving_flag = 0;
      uart_data->time = 0;
      uart_data->len = uart_data->count;
      uart_data->count = 0;
      uart_data->RXD_BUF[uart_data->len] = 0;
      uart_data->receive_complete_flag = 1;
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

static void UART1_IRQHandler(int irqno, void * param)
{
  uint8_t temp;
  rt_interrupt_enter();
  if(UART_Get_IIR_FLAG(UART1, UART_IIR_RXNE) == SET)
  {
    temp = UART_ReceiveData(UART1);
    uart_Data.RXD_BUF[uart_Data.count] = temp;
    uart_Data.count++;
    uart_Data.receiving_flag = 1;
    uart_Data.time = 0;
  }
  rt_interrupt_leave();
}
