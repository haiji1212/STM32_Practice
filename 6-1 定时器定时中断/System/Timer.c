#include "stm32f10x.h" 

extern uint16_t Num;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//开启TIM2的时钟，TIM2是通用定时器
	
	TIM_InternalClockConfig(TIM2);	//配置时钟源，配置TIM2为内部时钟：为了确定定时器的工作时钟来源
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	//定义TIM初始化变量
	//设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;	//ARR，计数周期
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;	//PSC，预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器，高级定时器才能用
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);	//配置TIM2时基单元
	
	//若不清除此标志位，则开启中断后，会立刻进入一次中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//清除定时器更新标志
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//开启TIM2的更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC分组为2
	NVIC_InitTypeDef NVIC_InitStructure;	//定义NVIC初始化变量
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	//选择配置NVIC的TIM2线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//指定NVIC路线使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC抢占优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//指定NVIC响应优先级为1
	NVIC_Init(&NVIC_InitStructure);	//配置NVIC
	
	TIM_Cmd(TIM2, ENABLE);	//使能TIM2
}

void TIM2_IRQHandler(void)	//此函数为中断函数，无需调用，中断触发后自动执行
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)	//判断是否是TIM2的更新事件触发的中断
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	//清除TIM2更新事件的中断标志位
	}		
}


