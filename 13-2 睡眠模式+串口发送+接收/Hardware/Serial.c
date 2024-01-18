#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxData;	//全局变量，保存串口接收数据
uint8_t Serial_RxFlag;	//全局变量，串口接收标志位

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//A9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;	//波特率为9600
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制：不需要
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//模式：Tx和Rx
	USART_InitStructure.USART_Parity = USART_Parity_No;	//校验位：无
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位：1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长：8位
	USART_Init(USART1, &USART_InitStructure);	//配置USART1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启串口接收数据的中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC为分组2
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	//选择配置NVIC的USART1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);	//配置NVIC
	
	USART_Cmd(USART1, ENABLE);	//USART1使能
}

void Serial_SendByte(uint8_t Byte)	//串口发送一字节数据
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完成
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}

void Serial_SendArray(uint8_t *Array, uint16_t length)	//串口发送数组
{
	uint16_t i;
	for(i = 0 ; i < length; i++)	//遍历数组，依次发送
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)	//串口发送字符串
{
	uint16_t i;
	for(i = 0 ; String[i] != '\0'; i++)	//遍历字符串
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)	//次方函数
{
	uint32_t result = 1;
	while(y--){
		result *= x;
	}
	return result;
}


void Serial_SendNumber(uint32_t Number, uint8_t Length)	//串口发送数字
{
	uint8_t i;
	for(i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)	//使用printf需要重定向的底层函数
{
	Serial_SendByte(ch);	//将printf的底层重定向到自己的发送字节函数
	return ch;
}

void Serial_Printf(char *format, ...)	//封装的prinf函数
{
	char String[100];				//定义字符数组
	va_list arg;					//定义可变参数列表数据类型的变量arg
	va_start(arg, format);			//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);					//结束变量arg
	Serial_SendString(String);		//串口发送字符数组（字符串）
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
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
