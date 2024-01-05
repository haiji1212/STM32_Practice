#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"

int main(void)
{
	OLED_Init();	//OLED初始化
	OLED_ShowChar(1, 1, 'A');	//在第一行第一列显示字符'A'
	OLED_ShowString(2, 1, "Hello world");	//从第二行第一列开始显示字符串"Hello world"
	OLED_ShowNum(3, 1, 520, 3);		//从第三行第一列开始显示3位数字520
	while(1)
	{

	}
} 
