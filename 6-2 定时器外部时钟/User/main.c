#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "timer.h"

uint16_t Num;
int main(void)
{
	OLED_Init();	//OLED初始化
	Timer_Init();	//定时器初始化
	OLED_ShowString(1, 1, "Num:");	
	OLED_ShowString(2, 1, "Cnt:");	
	
	while(1)
	{
		OLED_ShowNum(1, 5, Num, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);
	}
} 
