#include "interrupt.h"

void __interrupt() INTERRUPT_InterruptManager(void)
{
#if (defined PIC_SERIAL_ENABLED) && (defined PIC_SERIAL_RX_ENABLED)
    uart_irqhandler();
#endif // PIC_SERIAL_ENABLED
}