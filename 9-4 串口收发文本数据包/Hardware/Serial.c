#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxFlag;	//全局变量，保存接收标志位
char Serial_RxPacket[100];	//全局变量，保存接收数据包

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//A9，tx输出脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//A10，Rx输入脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;	//波特率设置为9600
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制：不设置
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//USART模式：tx模式和Rx模式均选择
	USART_InitStructure.USART_Parity = USART_Parity_No;	//校验位：无校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位：1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长：8位
	USART_Init(USART1, &USART_InitStructure);	//配置USART1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启串口接收数据的中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC分组为2
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	//选择配置NVIC的USART1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);	//使能USART1
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t length)
{
	uint16_t i;
	for(i = 0 ; i < length; i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint16_t i;
	for(i = 0 ; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	while(y--){
		result *= x;
	}
	return result;
}


void Serial_SendNumber(uint32_t Number, uint8_t Length)
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

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}	


uint8_t Serial_GetRxFlag(void)	//获取接收标志位
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}	

void USART1_IRQHandler(void)	//USART1中断
{
	static uint8_t RxState = 0;	//静态变量，标记接收状态机的状态
	static uint8_t pRxPacket = 0;	//静态变量，标记当前接收数据位置
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	//由USART1触发的中断
	{
		uint8_t RxData = USART_ReceiveData(USART1);	//读取数据寄存器
		if (RxState == 0)	//当前状态为0，接收包头
		{
			if (RxData == '@'&& Serial_RxFlag == 0)	//判断数据是否为包头@，且上一个数据包已处理完毕
			{
				RxState = 1;	//状态跳到1
				pRxPacket = 0;	//暂时未收到实际的数据包数据
			}
		}
		else if (RxState == 1)	//当前状态为1，接收实际的数据包数据
		{
			if(RxData == '\r')	//判断数据是否为第一个包尾\r
			{
				RxState = 2;	//状态跳到2
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;	//将数据存入数据包数组的指定位置
				pRxPacket ++;	//数据包的位置自增
			}
		}
		else if (RxState == 2)	//当前状态为2，接收第二个包尾\n
		{
			if (RxData == '\n')	//判断数据是否为第二个包尾0xFE
			{
				RxState = 0;	//状态跳到0，继续接收新的数据包
				Serial_RxFlag = 1;	//收到一个完整的数据包，接收标志位置1
				Serial_RxPacket[pRxPacket] = '\0';	//将收到的字符数据包添加一个字符串结束标志
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清理标志位
	}
}
