#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxData;	//全局变量，保存接收数据
uint8_t Serial_RxFlag;	//全局变量，保存接收标志位

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//A9,tx输出脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//A10,rx输入脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;	//波特率定义为9600
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制：不设置
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//USART模式：Tx和Rx均选择
	USART_InitStructure.USART_Parity = USART_Parity_No;	//校验位：无校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位：1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长：8位
	USART_Init(USART1, &USART_InitStructure);	//配置给USART1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启串口接收数据的中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC为分组2
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	//选择配置NVIC的USART1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);	//USART1使能
}

void Serial_SendByte(uint8_t Byte)	//发送字节数据
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t length)	//发送数组数据
{
	uint16_t i;
	for(i = 0 ; i < length; i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)	//发送字符串数据
{
	uint16_t i;
	for(i = 0 ; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)	//返回值X的Y次方
{
	uint32_t result = 1;
	while(y--){
		result *= x;
	}
	return result;
}


void Serial_SendNumber(uint32_t Number, uint8_t Length)	//发送数字
{
	uint8_t i;
	for(i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)	//自定义，发送字符数组
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}	

uint8_t Serial_GetRxFlag(void)	//获取串口接收标志位
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	else
		return 0;
}	

uint8_t Serial_GetRxData(void)	//获取串口接收的数据
{
	return Serial_RxData;
}

void USART1_IRQHandler(void)	//USART1中断函数
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	//是由USART1触发的中断
	//USART_IT_RXNE: Receive Data register not empty interrupt
	{
		Serial_RxData = USART_ReceiveData(USART1);	//读取接收寄存器
		Serial_RxFlag = 1;	//接收标志置1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清理标志位
	}
}
