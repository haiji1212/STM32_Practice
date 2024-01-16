#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "w25q64.h"

uint8_t MID;	//全局变量，保存MID
uint16_t DID;	//全局变量，保存DID
uint8_t ArrayWrite[] = {0x20, 0x23, 0x12, 0x19};	//全局变量，保存要写入的数据
uint8_t ArrayRead[4];	//全局变量，保存读出的数据

int main(void)
{
	OLED_Init();	
	W25Q64_Init();	//W25Q64初始化
	OLED_ShowString(1, 1, "MID:		 DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&MID, &DID);	//读取ID
	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);
	
	W26Q64_SectorErase(0x000000);	//扇区擦除
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);	//将写入数据的测试数组写入到W25Q64中
	W25Q64_ReadData(0x000000, ArrayRead, 4);	//读取刚写入的测试数据到读取数据的测试数组中
	
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	
	while(1)
	{

	}
} 
