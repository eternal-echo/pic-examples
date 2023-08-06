/*
 * File:   main.c
 * Author: henry
 *
 * Created on 2023年7月21日, 下午8:09
 */

#include "utils/utils.h"
#include "uart/uart.h"

void main(void) {
	uart_init(1, NULL);
	uart_printf("int example\r\n");

	while(1)
	{
        delay(1000);
	}
    return;
}
