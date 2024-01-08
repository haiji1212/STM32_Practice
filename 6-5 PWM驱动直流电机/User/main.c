#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "motor.h"
#include "key.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();	//OLED初始化
	Motor_Init();	//直流电机初始化
	Key_Init();		//按键初始化
	OLED_ShowString(1, 1, "speed:");
	while(1)
	{
		KeyNum = Key_GetNum();	//获取按键状态
		if(KeyNum == 1)	//B1被按下
		{
			Speed += 20;
			if(Speed > 100)	//Speed从-100递增到100，步长为20
				Speed = -100;
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1, 7, Speed, 3);
	}
} 
