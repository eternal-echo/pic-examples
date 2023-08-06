#include "interrupt.h"

void __interrupt() INTERRUPT_InterruptManager(void)
{
    uart_irqhandler();
}