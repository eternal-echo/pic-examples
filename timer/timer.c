#include "timer.h"

#ifdef PIC_TIMER_ENABLED

static uint16_t peroid_us = 0;
static void (*timer0_callback)(void) = 0;

void timer_init(uint16_t us, void (*callback)(void))
{
	GIE = 1; // 总中断使能
	PEIE = 1; // 外设中断使能

	TMR0IE = 1; // 定时器0中断使能
	TMR0IF = 0; // 定时器0中断标志位清零
	
    // bit 7 TMR0ON: Timer0 On/Off Control bit
    // 1 = Enables Timer0
    // 0 = Stops Timer0
    // bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit
    // 1 = Timer0 is configured as an 8-bit timer/counter
    // 0 = Timer0 is configured as a 16-bit timer/counter
    // bit 5 T0CS: Timer0 Clock Source Select bit
    // 1 = Transition on T0CKI pin
    // 0 = Internal instruction cycle clock (FOSC/4)
    // bit 4 T0SE: Timer0 Source Edge Select bit
    // 1 = Increment on high-to-low transition on T0CKI pin
    // 0 = Increment on low-to-high transition on T0CKI pin
    // bit 3 PSA: Timer0 Prescaler Assignment bit
    // 1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
    // 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
    // bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
    // 111 = 1:256 Prescale value
    // 110 = 1:128 Prescale value
    // 101 = 1:64 Prescale value
    // 100 = 1:32 Prescale value
    // 011 = 1:16 Prescale value
    // 010 = 1:8 Prescale value
    // 001 = 1:4 Prescale value
    // 000 = 1:2 Prescale value
	T0CON = 0x80; // 0000 1000

	// TMR0H = (65536-50000)/256;  //50ms
	// TMR0L = (65536-50000)%256;

    // Fosc / 4 = 1MHz
    peroid_us = us;
    TMR0H = (uint8_t)((65536 - peroid_us) / 256);
    TMR0L = (uint8_t)((65536 - peroid_us) % 256);
	
	TMR0ON = 1; // 定时器0使能

    timer0_callback = callback;
}

void timer_irqhandler(void)
{
    static uint8_t timerl = 0, timerh = 0;
	if(TMR0IF==1)
	{
		TMR0IF = 0; // 定时器0中断标志位清零
		TMR0ON = 0; // 定时器0关闭
        timerh = (uint8_t)((65536 - peroid_us) / 256);
        TMR0H = timerh;
        timerl = (uint8_t)((65536 - peroid_us) % 256);
        TMR0L = timerl;
		TMR0ON=1;
        if (timer0_callback != NULL)
        {
            timer0_callback();
        }
	}

}

#endif // PIC_TIMER_ENABLED