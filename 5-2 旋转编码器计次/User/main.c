#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "encoder.h"

int16_t Num;
int main(void)
{
	OLED_Init();	//OLED初始化
	Encoder_Init();	//编码器初始化
	OLED_ShowString(1, 1, "Num:");
	
	while(1)
	{
		Num += Encoder_Get();
		OLED_ShowSignedNum(1, 5, Num, 5);
	}
} 
