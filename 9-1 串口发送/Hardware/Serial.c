#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//A9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	USART_InitTypeDef USART_InitStructure;	//定义USART结构体变量
	USART_InitStructure.USART_BaudRate = 9600;	//波特率定义为9600
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制：不设置
	USART_InitStructure.USART_Mode = USART_Mode_Tx;	//USART模式：Tx发送
	USART_InitStructure.USART_Parity = USART_Parity_No;	//校验位：不校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位：1位	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长：8位
	USART_Init(USART1, &USART_InitStructure);	//配置给USART1
	
	USART_Cmd(USART1, ENABLE);	//使能USART1
}

void Serial_SendByte(uint8_t Byte)	//发送一个字节
{
	USART_SendData(USART1, Byte);	//将字节数据写入数据寄存器，写入后USART自动生成时序波形
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完成
	//USART_FLAG_TXE:  Transmit data register empty flag
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}

void Serial_SendArray(uint8_t *Array, uint16_t length)	//发送数组
{
	uint16_t i;
	for(i = 0 ; i < length; i++)	//遍历数组
	{
		Serial_SendByte(Array[i]);	//依次发送数组中的每个字节数据
	}
}

void Serial_SendString(char *String)	//发送字符串
{
	uint16_t i;
	for(i = 0 ; String[i] != '\0'; i++)	//遍历字符串数组
	{
		Serial_SendByte(String[i]);	//依次发送字符串数组中的每个字节数据
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	while(y--){
		result *= x;
	}
	return result;	//X的Y次方
}


void Serial_SendNumber(uint32_t Number, uint8_t Length)	//发送数字
{
	uint8_t i;
	for(i = 0; i < Length; i ++)	//遍历每一位
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);	//将printf的底层重定向到自己的发送字节函数
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;	//定义可变参数列表数据类型的变量arg
	va_start(arg, format);	//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);	//结束变量arg
	Serial_SendString(String);	//串口发送字符数组（字符串）
}	


