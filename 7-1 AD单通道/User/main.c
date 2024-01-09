#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "ad.h"

uint16_t ADValue;
float Voltage;
int main(void)
{
	OLED_Init();
	AD_Init();	//AD初始化
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Voltage:0.00V");
	while(1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3.3;	//电压转换计算
		OLED_ShowNum(1, 9, ADValue, 4);	//显示实时AD采样数据
		OLED_ShowNum(2, 9, Voltage, 1);	//显示电压个位数
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);	//显示电压小数位	
		Delay_ms(100);
	}
} 
