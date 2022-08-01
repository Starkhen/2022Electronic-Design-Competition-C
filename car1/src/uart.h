#ifndef _UART_H_
#define _UART_H_

#include <msp430.h>
#include "stdint.h"


void uart_init(void);
void UARTSendString(uint8_t *pbuff,uint8_t num);

#endif
