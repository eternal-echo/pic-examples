#ifndef __PIC_ADC_H__
#define __PIC_ADC_H__

#include "../config.h"
#ifdef PIC_ADC_ENABLED
void adc_init(uint16_t channel, void (*adc_callback)(float val));
float adc_get_val(void);
#ifdef PIC_ADC_INT_MODE
void adc_irqhandler(void);
#endif // PIC_ADC_INT_MODE
#endif // PIC_ADC_ENABLED

#endif // __PIC_ADC_H__