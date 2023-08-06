/*
 * File:   main.c
 * Author: henry
 *
 * Created on 2023年7月21日, 下午8:09
 */

#include "uart/uart.h"

#if (defined(PIC_SERIAL_ENABLED) && defined(PIC_SERIAL_RX_ENABLED))
void uart_rx_callback(uint8_t* pdata, uint16_t size)
{
	uart_transmit(pdata, size);
}
#endif // PIC_SERIAL_ENABLED && PIC_SERIAL_RX_ENABLED

void main(void) {
#ifdef PIC_SERIAL_ENABLED
#ifdef PIC_SERIAL_RX_ENABLED
	uart_init(1, uart_rx_callback);
#else
	uart_init(1, NULL);
#endif // PIC_SERIAL_RX_ENABLED
	uart_printf("example\r\n");
#endif // PIC_SERIAL_ENABLED
	while(1)
	{
        delay(1000);
	}
    return;
}
