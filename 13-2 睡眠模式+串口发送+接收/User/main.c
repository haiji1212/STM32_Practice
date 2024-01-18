#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"

uint8_t RxData;	//全局变量，保存接收数据

int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "RxData:");
	Serial_Init();	//串口初始化
	while(1)
	{
		if(Serial_GetRxFlag() == 1)	//收到数据
		{
			RxData = Serial_GetRxData();	//获取接收到的数据
			Serial_SendByte(RxData);		//发送数据
			OLED_ShowHexNum(1, 8, RxData, 2);
		}
		OLED_ShowString(2, 1, "Running");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500);
		
		__WFI();	//执行WFI指令，CPU睡眠，并等待中断唤醒
	}
} 
