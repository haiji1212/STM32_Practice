#include "stm32f10x.h"

uint16_t AD_Value[4];	//全局变量，用于存放AD转换结果

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		//开启DMA1时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//ADC_CLK时钟分频：6分频
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//模拟输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//A0 & A1 & A2 & A3
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//规则组通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//连续转换：使能
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据对齐：右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//外部触发：软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC模式：独立模式，即单独使用DMA1
	ADC_InitStructure.ADC_NbrOfChannel = 4;	//通道数设置为4
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//扫描模式：使能
	ADC_Init(ADC1, &ADC_InitStructure);

	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	//外设基地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//外设数据宽度：半字（2字节）
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址自增：失能
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;	//存储器基地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	//存储器数据宽度：半字（2字节）
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//存储器地址自增：使能
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//数据传输方向：外设到存储器
	DMA_InitStructure.DMA_BufferSize = 4;	//转运数据的大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	//DMA模式：循环模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	//存储器到存储器：失能
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	//优先级：中等
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//配置DMA1的通道1
	
	DMA_Cmd(DMA1_Channel1, ENABLE);	//DMA1的通道1使能
	ADC_DMACmd(ADC1, ENABLE);	//ADC1触发DMA1的信号使能
	ADC_Cmd(ADC1, ENABLE);	//ADC1使能
	
	//ADC校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	//ADC1触发
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//由于处于连续转换模式，所以触发一次之后可以连续工作
}
