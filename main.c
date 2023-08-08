/*
 * File:   main.c
 * Author: henry
 *
 * Created on 2023年7月21日, 下午8:09
 */

#include "uart/uart.h"
#include "adc/adc.h"

static uint16_t adc_channel = 4U;
#ifdef PIC_ADC_INT_MODE

void adc_complete_callback(float val)
{

	delay(500);
}
#endif // PIC_ADC_INT_MODE

void main(void) {
#ifdef PIC_ADC_ENABLED
	float voltage = 0;
	uart_init(1U, NULL);
#ifdef PIC_ADC_INT_MODE
	adc_init(adc_channel, adc_complete_callback);
#else
	adc_init(adc_channel, NULL);
#endif // PIC_ADC_INT_MODE

	uart_printf("example\r\n");

	while(1)
	{
#ifdef PIC_ADC_INT_MODE

#else
		voltage = adc_get_val();
		uart_printf("voltage: %f\r\n", voltage);
#endif // PIC_ADC_INT_MODE
        delay(500);
	}
    return;
#endif // PIC_ADC_ENABLED
}
