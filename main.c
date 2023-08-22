/*
 * File:   main.c
 * Author: henry
 *
 * Created on 2023年7月21日, 下午8:09
 */

#include "uart/uart.h"
#include "timer/timer.h"
#include "gpio/gpio.h"
#include "adc/adc.h"

void main(void) {
	uart_init(1, NULL);
	uart_printf("example\n");
	while(1)
	{
		__delay_ms(1000);
	}
    return;
}