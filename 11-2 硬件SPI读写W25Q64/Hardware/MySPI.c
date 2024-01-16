#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue){	//写SS电平
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

void MySPI_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//开启SPI1
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	//A4
	//A4:SS
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;	//A5 & A7
	//A5:SCK	A7:MOSI
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//A6
	//A6:MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	SPI_InitTypeDef SPI_InitStructure;	//定义SPI初始化结构体。注意：这里是SPI模式0
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	//波特率分频:128
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//奇数边沿采样
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//空闲时，SCK为低电平
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC多项式，暂时不用，给默认值7
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//数据宽度：8位
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//方向：2线全双工
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//高位先行
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	//SPI主模式
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	//NSS由软件控制
	SPI_Init(SPI1, &SPI_InitStructure);	//配置SPI1
	
	SPI_Cmd(SPI1, ENABLE);	//使能SPI1
	
	MySPI_W_SS(1);	//SS默认设置为高电平
}

void MySPI_Start(void){	//SPI起始信号
	MySPI_W_SS(0);	//拉低SS
}

void MySPI_Stop(void){	//SPI终止信号
	MySPI_W_SS(1);	//拉高SS
}

uint8_t MySPI_SwapByte(uint8_t ByteSend){	//SPI交换传输一个字节，使用SPI模式0
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);	//等待发送数据寄存器空
	//SPI_I2S_FLAG_TXE: Transmit buffer empty flag
	SPI_I2S_SendData(SPI1, ByteSend);	//写入数据到发送数据寄存器，开始产生时序
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);	//等待接收数据寄存器非空
	//SPI_I2S_FLAG_RXNE: Receive buffer not empty flag
	return SPI_I2S_ReceiveData(SPI1);	//读取接收到的数据并返回
}

