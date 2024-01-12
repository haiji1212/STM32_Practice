#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"

uint8_t RxData;

int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "RxData:");
	Serial_Init();	//串口初始化
	while(1)
	{
		if(Serial_GetRxFlag() == 1)	//若串口标志位置1，即接收到数据
		{
			RxData = Serial_GetRxData();	//传入接收的数据
			Serial_SendByte(RxData);	//将接收到的数据发送出去
			OLED_ShowHexNum(1, 8, RxData, 2);
		}
	}
} 
