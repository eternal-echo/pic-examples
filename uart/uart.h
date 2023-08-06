#ifndef __PIC_UART_H__
#define __PIC_UART_H__

#include "../config.h"

#ifdef PIC_SERIAL_ENABLED

void uart_init(uint8_t enable_receive, void (*uart_rx_callback)(uint8_t* pdata, uint16_t size));
void uart_transmit(const uint8_t *dat, uint16_t size);
void uart_printf(const char *fmt, ...);
#ifdef PIC_SERIAL_RX_ENABLED
void uart_irqhandler(void);
#endif // PIC_SERIAL_RX_ENABLED

#endif // PIC_SERIAL_ENABLED

#endif // __PIC_UART_H__