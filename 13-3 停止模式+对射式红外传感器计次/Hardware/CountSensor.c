#include "stm32f10x.h"

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//开启AFIO时钟
	//外部中断必须开启AFIO的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;		//A14
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);	
	
	EXTI_InitTypeDef EXTI_InitStructure;	//定义EXTI结构体变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;	//选择配置外部中断的14号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);	//配置EXTI
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC为分组2
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);	//配置NVIC
}

uint16_t CountSensor_Get(void)	//获取传感器计数值
{
	return CountSensor_Count;
}
	
void EXTI15_10_IRQHandler(void)	//中断函数
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)	//判断是否是外部中断14号线触发的中断
	{
		CountSensor_Count ++;	//计数值自增一次
		EXTI_ClearITPendingBit(EXTI_Line14);	//清除外部中断14号线的中断标志位
	}
		
}

