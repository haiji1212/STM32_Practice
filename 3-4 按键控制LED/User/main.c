#include "stm32f10x.h"  	                // Device header
#include "delay.h"
#include "led.h"
#include "key.h"

uint8_t KeyNum;

int main(void)
{
	LED_Init();		//LED初始化
	Key_Init();		//key初始化
	while(1)
	{
		KeyNum = Key_GetNum();	//获取按键状态
		if(KeyNum == 1){	//B1被按下
			LED1_Turn();	//LED1反转
		}
		if(KeyNum == 2){	//B11被按下
			LED2_Turn();	//LED2反转
		}
	}
} 
