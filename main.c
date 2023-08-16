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

#define LED_PIN 2

static uint8_t led_indicate = 0;

/**
 * @brief 定时器回调函数
 * 
 */
static void timer_callback(void)
{
	static uint8_t led_state = 0;
	static uint16_t cnt = 0;
	// 1000 0000 us = 1s
	if(cnt++ == 1000)
	{
		cnt = 0;
		led_state = !led_state;
		gpio_pin_write(D, LED_PIN, led_state);
		led_indicate = 1;
	}
}

void main(void) {
	gpio_pin_init(C, 0, GPIO_OUTPUT);
	gpio_pin_write(C, 0, 1);
	gpio_pin_init(D, LED_PIN, GPIO_OUTPUT);
	adc_init(1, NULL); // 初始化ADC模块 AN1
	uart_init(1, NULL);
	timer_init(1000, timer_callback);
	uart_printf("timer and uart example\n");
	while(1)
	{
		// timer_callback();
		// __delay_ms(1000);

		 if(led_indicate == 1)
		 {
		 	led_indicate = 0;
		 	uart_printf("%f\n", adc_get_val());
		 }
	}
    return;
}