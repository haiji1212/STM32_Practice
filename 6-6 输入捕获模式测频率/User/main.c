#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "pwm.h"
#include "ic.h"

int main(void)
{
	OLED_Init();	//OLED初始化
	OLED_ShowString(1, 1, "Freq:00000Hz");
	PWM_Init();	//PWM初始化
	IC_Init();	//IC初始化
	PWM_SetPrescaler(720-1);	//设置PSC：PWM频率Freq = 72M / (PSC + 1) / ARR = 72M / 720 / 100
	PWM_SetCompare1(50);		//设置CCR：PWM占空比Duty = CCR / ARR = CCR / 100
	while(1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
	}
} 
