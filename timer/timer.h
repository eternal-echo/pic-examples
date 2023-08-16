#ifndef __PIC_TIMER_H__
#define __PIC_TIMER_H__

#include "../config.h"

#ifdef PIC_TIMER_ENABLED
void timer_init(uint16_t us, void (*callback)(void));
void timer_irqhandler(void);
#endif // PIC_TIMER_ENABLED

#endif // __PIC_TIMER_H__