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
	uart_printf("uart example\r\n");
	uart_printf("unsigned char size: %d\r\n", sizeof(unsigned char));
	uart_printf("unsigned short size: %d\r\n", sizeof(unsigned short));
	uart_printf("unsigned int size: %d\r\n", sizeof(unsigned int));
	uart_printf("unsigned long size: %d\r\n", sizeof(unsigned long));

	uart_printf("signed char size: %d\r\n", sizeof(signed char));
	uart_printf("signed short size: %d\r\n", sizeof(signed short));
	uart_printf("signed int size: %d\r\n", sizeof(signed int));
	uart_printf("signed long size: %d\r\n", sizeof(signed long));

	uart_printf("float size: %d\r\n", sizeof(float));
	uart_printf("double size: %d\r\n", sizeof(double));

	uart_printf("uint8_t size: %d\r\n", sizeof(uint8_t));
	uart_printf("uint16_t size: %d\r\n", sizeof(uint16_t));
	uart_printf("uint32_t size: %d\r\n", sizeof(uint32_t));
	uart_printf("uint64_t size: %d\r\n", sizeof(uint64_t));

	uart_printf("int8_t size: %d\r\n", sizeof(int8_t));
	uart_printf("int16_t size: %d\r\n", sizeof(int16_t));
	uart_printf("int32_t size: %d\r\n", sizeof(int32_t));
	uart_printf("int64_t size: %d\r\n", sizeof(int64_t));

	while(1)
	{
        delay(1000);
	}
    return;
}
