#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "lightsensor.h"

int main(void)
{
	Buzzer_Init();	//蜂鸣器初始化
	LightSensor_Init();		//光敏传感器初始化
	
	while(1)
	{
		if(LightSensor_Get() == 1)	//光敏传感器输出高电平，即光线强度未达到阈值
			Buzzer_ON();	//蜂鸣器发声
		else	//光敏传感器输出低电平，即光线强度达到阈值
			Buzzer_OFF();	//蜂鸣器不发声
	}
} 
