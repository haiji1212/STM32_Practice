#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "myrtc.h"

int main(void)
{
	OLED_Init();
	MyRTC_Init();	//RTC初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//开启PWR时钟
	//停止模式和待机模式一定要记得开启
	
	OLED_ShowString(1, 1, "CNT:");
	OLED_ShowString(2, 1, "ALR:");
	OLED_ShowString(3, 1, "ALRF:");
	
	PWR_WakeUpPinCmd(ENABLE);	//使能位于PA0的WKUP引脚，WKUP引脚上升沿唤醒待机模式
	
	//设定闹钟
	uint32_t Alarm = RTC_GetCounter() + 10;	//闹钟为唤醒后当前时间的后10s
	RTC_SetAlarm(Alarm);	//写入闹钟值到RTC的ALR寄存器
	OLED_ShowNum(2, 6, Alarm, 10);	//显示闹钟值
	
	while (1)
	{		
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);
		OLED_ShowString(4, 1, "Running");
		Delay_ms(500);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(500);	
		OLED_ShowString(4, 1, "STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(500);			
		
		OLED_Clear();	//OLED清屏，模拟关闭外部所有的耗电设备，以达到极度省电
		PWR_EnterSTANDBYMode();	//STM32进入停止模式，并等待指定的唤醒事件（WKUP上升沿或RTC闹钟）
		/*待机模式唤醒后，程序会重头开始运行*/
	}
} 
