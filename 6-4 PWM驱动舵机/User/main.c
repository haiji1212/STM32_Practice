#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "pwm.h"
#include "servo.h"
#include "key.h"

uint8_t KeyNum;
float Angle;

int main(void)
{
	OLED_Init();	//OLED初始化
	Servo_Init();	//舵机初始化
	Key_Init();	//按键初始化
	OLED_ShowString(1, 1, "angle:");
	while(1)
	{
		KeyNum = Key_GetNum();	//获取按键状态
		if(KeyNum == 1)	//B1按键被按下
		{
			Angle += 30;
			if(Angle > 180)	//Angle实现从0递增180，步长为30
				Angle = 0;		
		}
		Servo_SetAngle(Angle);	//设置舵机旋转角度
		OLED_ShowNum(1, 7, Angle, 3);
	}
} 
