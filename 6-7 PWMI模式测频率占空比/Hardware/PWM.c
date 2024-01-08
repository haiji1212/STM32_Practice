#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//开启TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//A0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);	//设置TIM2为内部时钟源
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//滤波器时钟不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;	//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;	//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器关
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//输出比较模式，选择PWM1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平输出有效
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能
	TIM_OCInitStructure.TIM_Pulse = 0;	//CCR默认设置为0
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	//设置通道1
	
	TIM_Cmd(TIM2, ENABLE);	//使能TIM2
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);	//设置CCR1
}

void PWM_SetPrescaler(uint16_t Prescaler)	//设置PSC的值
{
	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
}

