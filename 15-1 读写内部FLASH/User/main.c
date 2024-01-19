#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"
#include "store.h"

uint8_t KeyNum;	//全局变量，获取按键状态

int main(void)
{
	OLED_Init();
	Key_Init();
	Store_Init();	//参数存储模块初始化，在上电的时候将闪存的数据加载回Store_Data，实现掉电不丢失
	Store_Data[1] = 0x1111;
	Store_Data[2] = 0x2222;
	Store_Data[3] = 0x1111;
	Store_Data[4] = 0x2222;	
	OLED_ShowString(1, 1, "FLAG:");
	OLED_ShowString(2, 1, "Data:");
	while(1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1){	//B1按键被按下
			//测试数据自增
			Store_Data[1]++;
			Store_Data[2]++;
			Store_Data[3]++;
			Store_Data[4]++;
			Store_Save();	//将Store_Data的数据备份保存到闪存，实现掉电不丢失
		}
		if(KeyNum == 2){	//B11按键被按下
			Store_Clear();	//将Store_Data的数据全部清0
		}
	}
	OLED_ShowHexNum(1, 6, Store_Data[0], 4);
	OLED_ShowHexNum(3, 1, Store_Data[1], 4);
	OLED_ShowHexNum(3, 6, Store_Data[2], 4);
	OLED_ShowHexNum(4, 1, Store_Data[3], 4);
	OLED_ShowHexNum(4, 6, Store_Data[4], 4);
} 
