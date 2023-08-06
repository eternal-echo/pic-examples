#include "uart.h"

static void (*uart_receive_callback)(uint8_t* pdata, uint16_t size) = NULL;

// 参数：是否使能接收
void uart_init(uint8_t enable_receive, void (*uart_rx_callback)(uint8_t* pdata, uint16_t size))
{
	uart_receive_callback = uart_rx_callback;
	
	TRISC7 = 1;
	TRISC6 = 1;
	
	//波特率 16000000/(64 (25 + 1)) = 9600
	SPBRG = 25; 

	/* RCSTA：接收状态和控制寄存器 */
	// RCSTA = 0x90; //  1001 0000
	// bit 7 SPEN： 串口使能位
	// 	1 = 使能串口
	// 	0 = 禁止串口
	RCSTA |= (1U << 7);
	// bit 6 RX9： 9 位接收使能位
	// 	1 = 选择 9 位接收
	// 	0 = 选择 8 位接收
	// RX9 = 0 选择 8 位接收
	RCSTA &= ~(1U << 6);
	// bit 5 SREN： 单双同步位（同步模式下有效）
	// 	1 = 单同步位
	// 	0 = 双同步位
	RCSTA &= ~(1U << 5);
	// bit 4 CREN： 连续接收使能位
	// 	1 = 使能连续接收
	// 	0 = 禁止连续接收
	// 	注： 同步模式下 SREN/CREN 的优先级高于 TXEN。
	if(enable_receive)
	{
		RCSTA |= (1U << 4);
	}
	else
	{
		RCSTA &= ~(1U << 4);
	}
	// bit 3 ADDEN： 地址检测使能位（同步模式下有效）
	// 	1 = 使能地址检测
	// 	0 = 禁止地址检测
	// bit 2 FERR： 帧错误位
	// 	1 = 帧错误
	// 	0 = 无帧错误
	// bit 1 OERR： 溢出错误位
	// 	1 = 溢出错误
	// 	0 = 无溢出错误
	// bit 0 RX9D： 接收数据的第 9 位
	// 	该位可以是地址 / 数据位或奇偶校验位。
	RCSTA &= ~(0x0F << 0);


	
	/* TXSTA：发送状态和控制寄存器 
	* bit 7 CSRC： 时钟源选择位
		异步模式：
		忽略。
		同步模式：
		1 = 主控模式 （时钟来自内部 BRG）
		0 = 从动模式 （时钟来自外部时钟源）
	* bit 6 TX9： 9 位发送使能位
		1 = 选择 9 位发送
		0 = 选择 8 位发送
	* bit 5 TXEN： 发送使能位
		1 = 使能发送
		0 = 禁止发送
		注： 同步模式下 SREN/CREN 的优先级高于 TXEN。
	* bit 4 SYNC： EUSART 模式选择位
		1 = 同步模式
		0 = 异步模式
	* bit 3 SENDB： 发送间隔字符位
		异步模式：
		1 = 在下一次发送时发送 “同步中断”字符 （在完成时用硬件清零）
		0 = “同步中断”字符发送完成
		同步模式：
		忽略。
	* bit 2 BRGH： 高波特率选择位
		异步模式：
		1 = 高速
		0 = 低速
		同步模式：
		在此模式下未使用。
	* bit 1 TRMT： 发送移位寄存器状态位
		1 = TSR 空
		0 = TSR 满
		bit 0 TX9D： 发送数据的第 9 位
		该位可以是地址 / 数据位或奇偶校验位。*/
	
	// 将SYNC位清零
	TXSTA = 0x24; // 0010  0100
	// TXSTA &= ~(1U << 4);

	RCIE = 1; // 串口接收中断使能
	TXIE = 0; // 串口发送中断使能
	PEIE = 1; // 外设中断使能
	GIE = 1; // 总中断使能
}

static void uart_send(const uint8_t dat)
{
	while(!TXIF);
	TXREG = dat;
}

void uart_transmit(const uint8_t *dat, uint16_t size)
{
	uint16_t tx_cnt = 0;
	while(tx_cnt < size)
	{
		uart_send(dat[tx_cnt]);
		tx_cnt++;
	}
}

void uart_printf(const char *fmt, ...)
{
	va_list ap;
	char buf[256];
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);
	uart_transmit((const uint8_t *)buf, (uint16_t)strlen(buf));
}

void uart_irqhandler(void)
{
	uint8_t rx_dat;
	if(RCIF)
	{
		RCIF = 0;
		rx_dat = RCREG;
		if(uart_receive_callback != NULL)
		{
			uart_receive_callback(&rx_dat, 1);
		}
	}
}