#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "serial.h"

int main(void)
{
	OLED_Init();	//OLED初始化
	Serial_Init();	//串口初始化

	/*串口基本函数*/
	Serial_SendByte(0x41);				//串口发送一个字节数据0x41	
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};	//定义数组
	Serial_SendArray(MyArray, 4);		//串口发送一个数组	
	Serial_SendString("\r\nNum1=");		//串口发送字符串	
	Serial_SendNumber(111, 3);			//串口发送数字
	Serial_Printf("Hello\r\n");			//串口打印字符串，使用自己封装的函数实现printf的效果
	while(1)
	{

	}
} 
