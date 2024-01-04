#include "stm32f10x.h"                  // Device header
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOC时钟
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO结构体初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//模式设置为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);		//输出低电平->点亮LED
	while(1)
	{
		
	}
}
