#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"

int main(void)
{
	OLED_Init();
	Key_Init();
	OLED_ShowString(1, 1, "IWDG TEST");
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET){	//如果是独立看门狗复位
	//RCC_FLAG_IWDGRST: Independent Watchdog reset
		OLED_ShowString(2, 1, "IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500);  
		RCC_ClearFlag();	//清除标志位
	}
	else{	//否则，即为其他复位
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(500);  	
	}
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//独立看门狗写使能
	IWDG_SetPrescaler(IWDG_Prescaler_16);	//设置预分频为16
	IWDG_SetReload(2499);	//设置重装值为2499，独立看门狗的超时时间为1000ms
	//TIWDG = 16 * (2499 + 1) / 40000 = 1s
	IWDG_ReloadCounter();	//重装计数器，喂狗
	IWDG_Enable();	//独立看门狗使能
	
	while(1)
	{
		Key_GetNum();	//调用阻塞式的按键扫描函数，模拟主循环卡死
		IWDG_ReloadCounter();	//重装计数器，喂狗
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(200);			//喂狗间隔为200+600=800ms
		OLED_ShowString(4, 1, "    ");
		Delay_ms(600);
	}
} 
