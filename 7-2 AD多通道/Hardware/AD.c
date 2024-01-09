#include "stm32f10x.h"

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//配置ADC_CLK：6分频，72MHz/6 = 12MHz
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//模拟输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	//A0 & A1 & A2 &3
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*不在此处配置规则组序列，而是在每次AD转换前配置，这样可以灵活更改AD转换的通道*/
	
	ADC_InitTypeDef ADC_InitStructure;	//定义ADC结构体变量
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//单次转换，转换一次后停止需要手动控制才重新启动转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不需要外部触发，软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//单模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//设置通道数为1
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//失能扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);	//使能ADC1
	
	//ADC校准流程，固定流程，不可省
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(uint8_t ADC_Channel)	//获取AD转换的值
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	//在每次转换前，根据函数形参灵活更改规则组的通道1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//软件触发AD进行一次转换
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	//等待EOC标志位，即等待AD转换结束
	return ADC_GetConversionValue(ADC1);	//读寄存器，获取结果
}








