#ifndef __PIC_UART_H__
#define __PIC_UART_H__

#include "../utils/utils.h"

void uart_init(uint8_t enable_receive);
void uart_transmit(const uint8_t *dat, uint16_t size);
void uart_printf(const char *fmt, ...);
void uart_irqhandler(void);

#endif // __PIC_UART_H__