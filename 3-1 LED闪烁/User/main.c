#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO结构体初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	while(1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);	//写入低电平->LED亮
		Delay_ms(800);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);	//写入高电平->LED灭
		Delay_ms(500);
	}
} 
