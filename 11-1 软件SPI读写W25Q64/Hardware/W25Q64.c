#include "stm32f10x.h"                  // Device header
#include "myspi.h"
#include "w25q64_ins.h"

void W25Q64_Init(void){
	MySPI_Init();	//SPI初始化
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID){	//读取ID号，MID为工厂ID，DID为设备ID
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_JEDEC_ID);	//交换发送ID的指令
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//交换接收MID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//交换接收DID的高八位
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//交换接收DID的低八位
	MySPI_Stop();	//终止信号
}

void W25Q64_WriteEnable(void){	//写使能
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);	//交换发送写使能的指令
	MySPI_Stop();	//终止信号
}

void W25Q64_WaitBusy(void){	//等待忙
	uint32_t Timeout;
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);	//交换发送读状态寄存器1的指令
	Timeout = 100000;	//给定超时计数时间
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01){	//循环等待忙标志位
		Timeout --;	//等待时，计数值自减
		if(Timeout == 0)	break;
	}
	MySPI_Stop();	//终止信号
}

//页编程的起始地址，范围：0x000000~0x7FFFFF
//注意事项：写入的地址范围不能跨页
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count){	//页编程
	uint16_t i;
	W25Q64_WriteEnable();	//写使能
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);	//交换发送页编程指令
	MySPI_SwapByte(Address >> 16);	//交换发送地址的23~16位
	MySPI_SwapByte(Address >> 8);	//交换发送地址的15~8位
	MySPI_SwapByte(Address);		//交换发送地址的7~0位
	for(i = 0; i < Count; i ++){
		MySPI_SwapByte(DataArray[i]);	//交换发送要写入的数据
	}
	MySPI_Stop();	//终止信号
	W25Q64_WaitBusy();	//等待忙
}

//指定扇区的地址，范围：0x000000~0x7FFFFF
void W26Q64_SectorErase(uint32_t Address){	//扇区擦除(4KB)
	W25Q64_WriteEnable();	//写使能
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);	//交换发送擦除扇区指令
	MySPI_SwapByte(Address >> 16);	//交换发送地址的23~16位
	MySPI_SwapByte(Address >> 8);	//交换发送地址的15~8位
	MySPI_SwapByte(Address);		//交换发送地址的7~0位
	MySPI_Stop();	//终止信号
	W25Q64_WaitBusy();	//等待忙
}

//读取数据的起始地址，范围：0x000000~0x7FFFFF
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count){	//读取数据
	uint32_t i;
	MySPI_Start();	//起始信号
	MySPI_SwapByte(W25Q64_READ_DATA);	//发送读取数据指令
	MySPI_SwapByte(Address >> 16);	//交换发送地址的23~16位
	MySPI_SwapByte(Address >> 8);	//交换发送地址的15~8位
	MySPI_SwapByte(Address);		//交换发送地址的7~0位
	for(i = 0; i < Count; i ++){
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//交换接收数据
	}
	MySPI_Stop();	//终止信号
}
