# PIC18F4520 BSP
这是一个基于PIC18F4520的BSP，包含了一些常用的驱动，如GPIO、串口、中断、定时器、ADC、DAC等。

- [x] 配置项 config.h
- [x] delay和常用头文件：utils
- [x] GPIO：gpio
- [x] 串口：uart
- [x] 中断：interrupt
- [x] 定时器：timer
- [x] ADC：adc

## 注意事项
LED需要将RC0赋值为1，才能点亮。
按键S1和S2是一端接地另一端直接连接到RB2和RB3，电路设计有问题无法使用，缺少上拉电阻。