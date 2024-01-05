#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	//设置所有引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	while(1)
	{
		GPIO_Write(GPIOA, ~0x0001);	//点亮A0
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0002);	//点亮A1
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0004);	//点亮A2
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0008);	//点亮A3
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0010);	//点亮A4
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0020);	//点亮A5
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0040);	//点亮A6
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0080);	//点亮A7
		Delay_ms(500);
	}
} 
