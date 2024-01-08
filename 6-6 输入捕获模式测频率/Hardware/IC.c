#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//A6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);	//设置TIM3为内部时钟源
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//滤波器时钟不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;	//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;	//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器关
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//配置通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xf;	//输入滤波器参数
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//不分频，即每次信号都触发捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//直通，不交叉
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);	//触发源选择TIM_TS_TI1FP1
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);	//从模式选择复位。即TI1产生上升沿时，会触发CNT归零
	
	TIM_Cmd(TIM3, ENABLE);	//使能TIM3
}

uint32_t IC_GetFreq(void)	//获取输入捕获的频率
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);	//测周法得到频率fx = fc / N，这里不执行+1的操作也可
}




