#include "stm32f10x.h" 

extern uint16_t Num;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//开启TIM2的时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟

	GPIO_InitTypeDef GPIO_InitStructure;	//定义GPIO初始化变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//A0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
	//将TIM2设置为外部时钟源：不分频、高电平或上升沿有效、最后一个滤波器参数加到最大0x0F，可滤除时钟信号抖动
	//注意TIM2的ETR引脚固定为PA0，无法随意更改
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	//定义TIM初始化变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//滤波器时钟不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;	//ARR
	//ARR=10，即从0计数到9之后会触发中断
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;	//PSC
	//不分频，即每次触发CNT加一
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器关
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//清除TIM2更新标志
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//开启TIM2更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC分组为2
	NVIC_InitTypeDef NVIC_InitStructure;	//定义NVIC初始化变量
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM2, ENABLE);	//使能TIM2
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);	//返回定时器CNT计数值
}

void TIM2_IRQHandler(void)	//此函数为中断函数，无需调用，中断触发后自动执行
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) //判断是否是TIM2的更新事件触发的中断
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIM2更新事件的中断标志位
	}		
}


