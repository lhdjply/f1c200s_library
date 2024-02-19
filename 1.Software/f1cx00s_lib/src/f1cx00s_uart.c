#include "f1cx00s_uart.h"
#include "f1cx00s_ccu.h"

void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * UART_InitStruct)
{
  uint32_t val;
  UARTx->DLH_IER = 0x00; // close uart irq
  UARTx->IIR_FCR = 0x37; // config fifo
  UARTx->MCR = 0x00;     // config modem

  /* config baud */
  UARTx->LCR |= (1 << 7);
  val = APB_Get_clk() / (16 * UART_InitStruct->UART_BaudRate);
  UARTx->RBR_THR_DLL = val & 0xff;
  UARTx->DLH_IER = (val >> 8) & 0xff;
  UARTx->LCR &= ~(1 << 7);

  val = UARTx->LCR;
  val &= ~0x1f;
  if(UART_InitStruct->UART_Parity == UART_Parity_No)
  {
    val |= ((UART_InitStruct->UART_WordLength) << 0) |
           (UART_InitStruct->UART_StopBits << 2) |
           (0 << 3);
  }
  else
  {
    val |= ((UART_InitStruct->UART_WordLength) << 0) |
           (UART_InitStruct->UART_StopBits << 2) |
           (1 << 3) |
           (UART_InitStruct->UART_Parity << 4);
  }
  UARTx->LCR = val;

  UARTx->TFL = 0x0f;
  UARTx->RFL = 0x3f;
}

void UART_SendBaudRate(UART_TypeDef * UARTx, uint32_t BaudRate)
{
  uint32_t val;
  UARTx->LCR |= (1 << 7);
  val = APB_Get_clk() / (16 * BaudRate);
  UARTx->RBR_THR_DLL = val & 0xff;
  UARTx->DLH_IER = (val >> 8) & 0xff;
  UARTx->LCR &= ~(1 << 7);
}

void UART_SendData(UART_TypeDef * UARTx, uint16_t Data)
{
  UARTx->RBR_THR_DLL = Data;
}

uint16_t UART_ReceiveData(UART_TypeDef * UARTx)
{
  return (uint16_t)UARTx->RBR_THR_DLL;
}

FlagStatus UART_Get_Status(UART_TypeDef * UARTx, uint8_t USR_FLAG)
{
  if((UARTx->USR & USR_FLAG) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

void UART_ITConfig(UART_TypeDef * UARTx, uint8_t UART_IT, FunctionalState NewState)
{
  if(NewState == ENABLE)
  {
    UARTx->DLH_IER |= UART_IT;
  }
  else
  {
    UARTx->DLH_IER &= ~UART_IT;
  }
}

FlagStatus UART_Get_IIR_FLAG(UART_TypeDef * UARTx, uint8_t UART_IIR)
{
  if((UARTx->IIR_FCR & UART_IIR) == UART_IIR)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}
