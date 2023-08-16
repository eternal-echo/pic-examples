#include "adc.h"

#ifdef PIC_ADC_ENABLED

static void (*adc_complete_callback)(float val) = NULL;

static void adc_start(void)
{
	GODONE = 1; // 开始转换
}

void adc_init(uint16_t channel, void (*adc_callback)(float val))
{
	adc_complete_callback = adc_callback;

	TRISE=0xFF; // 设置为输入
	// TODO: 数字模拟复用端口状态设定需要根据参数改变
	ADCON1=0x07;   //设定 AN5\ AN6\ AN7 为模拟通道
	
	/* ADCON0寄存器设置 */
	// CHS3(bit 3) CHS2(bit 2) CHS1(bit 1) CHS0(bit 0) 通道选择位
	ADCON0 &= 0b11000011; // 清除通道选择位
	ADCON0 |= (channel & 0x0F) << 2; // 设置通道选择位
	// TODO: 通道验证
// 	// ADCON0=0x18;   //选通AN6通道
// 	// ADCON0=0x14;   //选通AN5通道
// 	// ADCON0=0x1C;   //选通AN7通道
//      ADCON0=0x10;   //选通AN4通道
// //	ADCON0 = 0x04; //选通AN1通道

//	ADCON2=0xBA;  //右对齐、20TAD、32TOSC时钟
	ADCON2=0x94;  //右对齐、4TAD、  4TOSC时钟
	ADON=1; // 开启ADC模块
#ifdef PIC_ADC_INT_MODE
	GIE=1; // 开启全局中断
	ADIE=1; // 开启ADC中断
	ADIF=0; // 清除ADC中断标志
	PEIE=1; // 开启外设中断
	delay(5);
	GODONE=1; // 开始转换
#endif // PIC_ADC_INT_MODE
}

float adc_get_val(void)
{
	float adc_val;
	adc_start();
	while(GODONE == 1);
	adc_val = ADRESH << 8 | ADRESL;
	adc_val = adc_val * 5 / 1023;
	return adc_val;
}

#ifdef PIC_ADC_INT_MODE
void adc_irqhandler(void)
{
	float adc_val;
	if(ADIF == 1)
	{
		ADIF = 0;
		adc_val = ADRESH << 8 | ADRESL;
		adc_val = adc_val * 5 / 1023;
		if(adc_complete_callback != NULL)
		{
			adc_complete_callback(adc_val);
		}
	}
}
#endif // PIC_ADC_INT_MODE
#endif // PIC_ADC_ENABLED