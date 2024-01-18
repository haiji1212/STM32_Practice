#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "countsensor.h"

int main(void)
{
	OLED_Init();
	CountSensor_Init();	//对射式红外传感器初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//开启PWR时钟
	OLED_ShowString(1, 1, "count:");
	while(1)
	{
		OLED_ShowNum(1, 7, CountSensor_Get(), 5);		
		OLED_ShowString(2, 1, "Running");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500); 
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);	//STM32进入停止模式，并等待中断唤醒
		SystemInit();	//唤醒后，要重新配置时钟
	}
} 
