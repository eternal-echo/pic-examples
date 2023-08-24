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

#define BUTTON1_PORT GPIO_PORT_B
#define BUTTON2_PORT GPIO_PORT_B
#define BUTTON1_PIN GPIO_PIN_2
#define BUTTON2_PIN GPIO_PIN_3

void main(void) {
	uart_init(1, NULL);
	uart_printf("button example\n");
	gpio_pin_init(BUTTON1_PORT, BUTTON1_PIN, GPIO_MODE_INPUT);
	gpio_pin_init(BUTTON2_PORT, BUTTON2_PIN, GPIO_MODE_INPUT);
	while(1)
	{
		uart_printf("button1: %d, button2: %d\n", gpio_pin_read(BUTTON1_PORT, BUTTON1_PIN), gpio_pin_read(BUTTON2_PORT, BUTTON2_PIN));
		__delay_ms(1000);
	}
    return;
}