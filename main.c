/*
 * File:   main.c
 * Author: henry
 *
 * Created on 2023年7月21日, 下午8:09
 */

#include "uart/uart.h"

void main(void) {
#ifdef PIC_SERIAL_ENABLED
	uart_init(1, NULL);
	uart_printf("example\r\n");
#endif // PIC_SERIAL_ENABLED
	while(1)
	{
        delay(1000);
	}
    return;
}
