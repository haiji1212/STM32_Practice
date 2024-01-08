#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	//电机输入引脚 A4 A5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	PWM_Init();	//PWM初始化
}

void Motor_SetSpeed(int8_t Speed)
{
	if(Speed >= 0)	//设置正转的速度
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);	//A4置高
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	//A5置低
		PWM_SetCompare3(Speed);	//设置速度
	}
	else	//设置反转的速度
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);	//A4置低
		GPIO_SetBits(GPIOA, GPIO_Pin_5);	//A5置高
		PWM_SetCompare3(-Speed);	//设置速度，因为参数只能是正数，所以取反
	}
}

