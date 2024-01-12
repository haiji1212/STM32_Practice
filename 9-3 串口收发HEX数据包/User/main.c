#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"
#include "key.h"

uint8_t KeyNum;	//全局变量，保存按键状态

int main(void)
{
	OLED_Init();
	Key_Init();
	Serial_Init();	//串口初始化
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");
	
	//定义发送数据包
	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;
	
	while(1)
	{
		KeyNum = Key_GetNum();	//获取按键状态
		if(KeyNum == 1){	//检测到B1被按下
			//发送数据包自增
			Serial_TxPacket[0] ++;		
			Serial_TxPacket[1] ++;			
			Serial_TxPacket[2] ++;		
			Serial_TxPacket[3] ++;
			Serial_SendPacket();	//发送数据包
			OLED_ShowHexNum(2, 1, Serial_TxPacket[0], 2);
			OLED_ShowHexNum(2, 4, Serial_TxPacket[1], 2);
			OLED_ShowHexNum(2, 7, Serial_TxPacket[2], 2);
			OLED_ShowHexNum(2, 10, Serial_TxPacket[3], 2);
		}			
		if(Serial_GetRxFlag()==1)	//当收到一个完整的包
		{
			OLED_ShowHexNum(4, 1, Serial_RxPacket[0], 2);
			OLED_ShowHexNum(4, 4, Serial_RxPacket[1], 2);
			OLED_ShowHexNum(4, 7, Serial_RxPacket[2], 2);
			OLED_ShowHexNum(4, 10, Serial_RxPacket[3], 2);
		}
	}
} 
