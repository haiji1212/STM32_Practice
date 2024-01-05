#include "stm32f10x.h"

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//开启AFIO时钟，外部中断必须开启AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);	//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	
	EXTI_InitTypeDef EXTI_InitStructure;	//EXTI结构体初始化
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;		//选择配置外部中断的14号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);	//将结构体变量交给EXTI_Init，配置EXTI外设
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC为分组2
	NVIC_InitTypeDef NVIC_InitStructure;	//NVIC结构体初始化
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);	//将结构体变量交给NVIC_Init，配置NVIC外设
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;	//获取传感器计数值
}

void EXTI15_10_IRQHandler(void)	//函数名为预留的指定名称，可以从启动文件复制
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)	//判断是否由外部中断14号线触发的中断
	{
		CountSensor_Count ++;
		EXTI_ClearITPendingBit(EXTI_Line14);	//清除外部中断14号线的中断标志位
	}
		
}



