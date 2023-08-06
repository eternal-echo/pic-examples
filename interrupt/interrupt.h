#ifndef __PIC_INTERRUPT_H__
#define __PIC_INTERRUPT_H__

#include "../config.h"
#if (defined PIC_SERIAL_ENABLED) && (defined PIC_SERIAL_RX_ENABLED)
#include "../uart/uart.h"
#endif // PIC_SERIAL_ENABLED

#endif // __PIC_INTERRUPT_H__