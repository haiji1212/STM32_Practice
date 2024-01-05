#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "countsensor.h"

int main(void)
{
	OLED_Init();	//OLED初始化
	CountSensor_Init();
	OLED_ShowString(1, 1, "count:");
	
	while(1)
	{
		OLED_ShowNum(1, 7, CountSensor_Get(), 5);
	}
} 
