#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"

uint8_t KeyNum;	//全局变量，保存按键状态
uint16_t ArrayWrite[] = {0x1234, 0x5678};	//全局变量，定义要写入的数组
uint16_t ArrayRead[2];	//全局变量，定义要读的数组

int main(void) 
{
	OLED_Init();
	Key_Init();
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);	//开启BKP时钟
	PWR_BackupAccessCmd(ENABLE);	//备份寄存器访问使能
	while(1)
	{
		KeyNum = Key_GetNum();	//获取按键状态
		if(KeyNum == 1){	//B1被按下
			//写入数组在写入之前自增
			ArrayWrite[0] ++;
			ArrayWrite[1] ++;
			//写入数据到备份寄存器
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);
			OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);
			OLED_ShowHexNum(1, 8, ArrayWrite[1], 4);
		}
		//读取备份寄存器的数据
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		OLED_ShowHexNum(2, 3, ArrayRead[0], 4);
		OLED_ShowHexNum(2, 8, ArrayRead[1], 4);
	}
} 
