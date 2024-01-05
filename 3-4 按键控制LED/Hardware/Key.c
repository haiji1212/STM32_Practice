#include "stm32f10x.h"                  // Device header
#include "delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输出，默认为高电平
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;		//初始化变量，用于后续保存按键按下状态
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)	//读到B1为低电平，即B1按键被按下
	{
		Delay_ms(20);	//消抖，延时20ms
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);	//B1仍为低电平，即B1按键仍处于被按下的状态
		Delay_ms(20);	//消抖，延时20ms
		KeyNum = 1;		//变量置1，表示B1被按下
	}
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)	//读到B11为低电平，即B11按键被按下
	{
		Delay_ms(20);	//消抖，延时20ms
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);	//B11仍为低电平，即B11按键仍处于被按下的状态
		Delay_ms(20);	//消抖，延时20ms
		KeyNum = 2;		//变量置2，表示B11被按下
	}
	return KeyNum;	//返回状态值。如果没有按键被按下，则返回默认初始值0
}

