#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "timer.h"
#include "encoder.h"

int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1, 1, "CNT:");	
	while(1)
	{
		OLED_ShowSignedNum(1, 5, Encoder_Get(), 5);
	}
} 
