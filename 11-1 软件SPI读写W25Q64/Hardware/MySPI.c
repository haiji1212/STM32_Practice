#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue){	//写SS电平
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

void MySPI_W_SCK(uint8_t BitValue){	//写SCK电平
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue){	//写MOSI电平
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

uint8_t MySPI_R_MISO(void){	//读MISO电平
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;	//A4 & A5 & A7
	//A4:SS		A5:SCK		A7:MOSI
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//A6
	//A6:MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	MySPI_W_SS(1);	//SS默认设置为高电平
	MySPI_W_SCK(0);	//SCK默认设置为低电平
}

void MySPI_Start(void){	//SPI起始信号
	MySPI_W_SS(0);	//拉低SS
}

void MySPI_Stop(void){	//SPI终止信号
	MySPI_W_SS(1);	//拉高SS
}

uint8_t MySPI_SwapByte(uint8_t ByteSend){	//SPI交换传输一个字节，使用SPI模式0
	uint8_t ByteReceive = 0x00;
	uint8_t i;
	for(i = 0; i < 8; i ++){	//循环8次，依次交换每一位数据
		MySPI_W_MOSI(ByteSend & (0x80 >> i));	//使用掩码的方式取出ByteSend的指定一位数据并写入到MOSI线		
		MySPI_W_SCK(1);	//拉高SCK，上升沿移出数据
		if(MySPI_R_MISO() == 1){	//读取MISO数据，并存储到Byte变量
			ByteReceive |= (0x80 >> i);	//当MISO为1时，置变量指定位为1，当MISO为0时，不做处理，指定位为默认的初值0
		}
		MySPI_W_SCK(0);	//拉低SCK，下降沿移入数据
	}
	return ByteReceive;	//返回接收到的一个字节数据
}

