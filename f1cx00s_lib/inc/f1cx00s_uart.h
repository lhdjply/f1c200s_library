#ifndef __F1CX00S_UART__H
#define __F1CX00S_UART__H

#include "f1cx00s.h"

#define UART_WordLength_5b 0x00
#define UART_WordLength_6b 0x01
#define UART_WordLength_7b 0x02
#define UART_WordLength_8b 0x03

#define UART_StopBits_1 0x00
#define UART_StopBits_1_5 0x01

#define UART_Parity_Odd 0
#define UART_Parity_Even 1
#define UART_Parity_No 2

#define UART_IT_ERBFI 0x01
#define UART_IT_ETBEI 0x02
#define UART_IT_ELSI 0x04
#define UART_IT_EDSSI 0x08
#define UART_IT_PTIME 0x80

#define UART_USR_RFF 0x10
#define UART_USR_RFNE 0x08
#define UART_USR_TFE 0x04
#define UART_USR_TFNF 0x02
#define UART_USR_BUSY 0x01

#define UART_IIR_FEFLAG 0xC0
#define UART_IIR_MODEM 0x00
#define UART_IIR_NONE 0x01
#define UART_IIR_THR 0x02
#define UART_IIR_RXNE 0x04
#define UART_IIR_RXLINE 0x06
#define UART_IIR_BUSY 0x07
#define UART_IIR_TIMEOUT 0x0C

typedef struct
{
  uint32_t UART_BaudRate;
  uint16_t UART_WordLength;
  uint16_t UART_StopBits;
  uint16_t UART_Parity;
} UART_InitTypeDef;

void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * UART_InitStruct);
void USART_SendData(UART_TypeDef * UARTx, uint16_t Data);
uint16_t UART_ReceiveData(UART_TypeDef * UARTx);
FlagStatus UART_Get_Status(UART_TypeDef * UARTx, uint8_t USR_FLAG);
void UART_ITConfig(UART_TypeDef * UARTx, uint8_t UART_IT, FunctionalState NewState);
FlagStatus UART_Get_IIR_FLAG(UART_TypeDef * UARTx, uint8_t UART_IIR);
#endif
