#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"

int main(void)
{
	OLED_Init();
	Key_Init();
	OLED_ShowString(1, 1, "WWDG TEST");
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET){	//如果是窗口看门狗复位
	//RCC_FLAG_WWDGRST: Window Watchdog reset
		OLED_ShowString(2, 1, "WWDGRST");
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	//开启WWDG的时钟
	WWDG_SetPrescaler(WWDG_Prescaler_8);	//设置预分频为8
	//注意往寄存器里写值需要 | 0x40
	WWDG_SetWindowValue((54 - 33) | 0x40);	//设置窗口值，窗口时间为30ms
	//WR = 4096 * 8 * (54-33+1) / 36000000 = 20ms
	//对应窗口值为 50 - 20 = 30ms
	WWDG_Enable(54 | 0x40);	//使能并第一次喂狗，超时时间为50ms
	//4096 * 8 * (54+1) / 36000000 = 50ms
	//T[5:0] = 54
	
	while(1)
	{
		Key_GetNum();	//调用阻塞式的按键扫描函数，模拟主循环卡死
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);
		OLED_ShowString(4, 1, "    ");	
		Delay_ms(20);	//喂狗间隔为20+20=40ms
		WWDG_SetCounter(54 | 0x40);	//重装计数器，喂狗
	}
} 
