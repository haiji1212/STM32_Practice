#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"
#include "key.h"
#include "led.h"
#include "string.h"

int main(void)
{
	OLED_Init();	
	Serial_Init();	//串口初始化
	LED_Init();
	OLED_ShowString(1, 1, "hi");
	while(1)
	{
		if(Serial_GetRxFlag()==1)
		{
			OLED_ShowString(4, 1, "				");
			OLED_ShowString(4, 1, Serial_RxPacket);
			
			if(strcmp(Serial_RxPacket, "111") == 0)	//如果收到的数据包是111
				LED1_ON();	//灯亮
			else	//收到其他数据
				LED1_OFF();	//灯灭
		}
	}
} 
