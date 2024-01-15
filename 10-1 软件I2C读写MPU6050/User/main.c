#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "mpu6050.h"

uint16_t ID;	//全局变量，保存芯片ID
int16_t AX, AY, AZ, GX, GY, GZ;	//全局变量，保存六轴数据

int main(void)
{
	OLED_Init();	//OLED初始化
	MPU6050_Init();	//MPU6050初始化
	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();	//获取ID
	OLED_ShowHexNum(1, 4, ID, 2);
	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);	//获取六轴数据
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
} 
