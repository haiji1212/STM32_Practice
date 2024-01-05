#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//低电平驱动蜂鸣器发声
		Delay_ms(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	//蜂鸣器不发声
		Delay_ms(10);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//低电平驱动蜂鸣器发声
		Delay_ms(800);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	//蜂鸣器不发声
		Delay_ms(200);
	}
} 
