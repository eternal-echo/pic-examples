#ifndef __PIC_INTERRUPT_H__
#define __PIC_INTERRUPT_H__

#include "../config.h"

#if (defined PIC_SERIAL_ENABLED) && (defined PIC_SERIAL_RX_ENABLED)
#include "../uart/uart.h"
#endif // PIC_SERIAL_ENABLED

#if (defined PIC_ADC_ENABLED) && (defined PIC_ADC_INT_MODE)
#include "../adc/adc.h"
#endif // PIC_ADC_ENABLED

#if (defined PIC_TIMER_ENABLED)
#include "../timer/timer.h"
#endif // PIC_TIMER_ENABLED

#endif // __PIC_INTERRUPT_H__