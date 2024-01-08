#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "pwm.h"

uint8_t i;
int main(void)
{
	OLED_Init();	//OLED初始化
	PWM_Init();		//PWM初始化
	while(1)
	{
		for(i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(i);	//依次将定时器的CCR寄存器设置为0~100，PWM占空比逐渐增大，LED逐渐变亮
			Delay_ms(20);
		}
		for(i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(100-i);	//依次将定时器的CCR寄存器设置为100~0，PWM占空比逐渐减小，LED逐渐变暗
			Delay_ms(20);
		}
	}
} 
