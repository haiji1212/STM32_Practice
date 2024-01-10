#include "stm32f10x.h"

uint16_t MyDMA_Size = 0;	//定义全局变量，保存Init中传入的size，供给Transfer

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t size)
{
	MyDMA_Size = size;	//保存传入的size，后续提供给Transfer使用
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
	
	DMA_InitTypeDef DMA_InitStructure;	//定义DMA结构体变量
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;	//外设基地址：给定AddrA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据宽度：字节
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;	//外设地址自增：使能
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;	//存储器基地址：给定AddrB
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//存储器数据宽度：字节
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//存储器地址自增：使能
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//数据传输方向：外设到存储器
	//这里并没有存储器到存储器的方向选择，当使用存储器到存储器时，只需要把其中一个存储器当作外设使用即可。
	DMA_InitStructure.DMA_BufferSize = size;	//转运的数据大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	//DMA模式：正常模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;	//存储器到存储器：使能
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	//优先级：中等
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//配置DMA1的通道1
	
	DMA_Cmd(DMA1_Channel1, DISABLE);	
	//这里先不给使能，初始化后不会立刻工作，等后续调用Transfer后，再开始
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);	//失能DMA1的通道1。在写入传输计数器之前，需要DMA暂停工作
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);	//写入传输计数器，指定将要转运的数据大小
	DMA_Cmd(DMA1_Channel1, ENABLE);	//使能DMA1的通道1
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);	//等待DMA工作完成
	//DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag
	DMA_ClearFlag(DMA1_FLAG_TC1);	//清除标志位
}

