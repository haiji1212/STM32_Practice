#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "ad.h"

uint16_t AD0, AD1, AD2, AD3;

int main(void)
{
	OLED_Init();
	AD_Init();	//AD初始化
	OLED_ShowString(1, 1, "AD0:");
	OLED_ShowString(2, 1, "AD1:");
	OLED_ShowString(3, 1, "AD2:");
	OLED_ShowString(4, 1, "AD3:");
	while(1)
	{
		AD0 = AD_GetValue(ADC_Channel_0);	//获取通道0的AD数据
		AD1 = AD_GetValue(ADC_Channel_1);	//获取通道1的AD数据
		AD2 = AD_GetValue(ADC_Channel_2);	//获取通道2的AD数据
		AD3 = AD_GetValue(ADC_Channel_3);	//获取通道3的AD数据
		OLED_ShowNum(1, 5, AD0, 4);
		OLED_ShowNum(2, 5, AD1, 4);
		OLED_ShowNum(3, 5, AD2, 4);
		OLED_ShowNum(4, 5, AD3, 4);		
		Delay_ms(100);
	}
} 
