#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void Servo_Init(void)
{
	PWM_Init();	//PWM初始化
}

void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);	//将角度线性变换，对应到舵机要求的占空比范围上
	//0°对应500，180°对应2500，因此可以得到映射关系
}
