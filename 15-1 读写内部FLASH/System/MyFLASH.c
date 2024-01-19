#include "stm32f10x.h"

uint32_t MyFLASH_ReadWord(uint32_t Address){	//FLASH读取一个32位的字
	return *((__IO uint32_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

uint16_t MyFLASH_ReadHalfWord(uint32_t Address){	//FLASH读取一个16位的半字
	return *((__IO uint16_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

uint8_t MyFLASH_ReadByte(uint32_t Address){		//FLASH读取一个8位的字节
	return *((__IO uint8_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

void MyFLASH_EraseAllPages(void){	//FLASH全擦除
	FLASH_Unlock();	//解锁
	FLASH_EraseAllPages();	//全擦除
	FLASH_Lock();	//加锁
}

void MyFLASH_ErasePage(uint32_t PageAddress){	//FLASH页擦除
	FLASH_Unlock();	//解锁
	FLASH_ErasePage(PageAddress);	//页擦除
	FLASH_Lock();	//加锁
}

void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data){	//FLASH编程字
	FLASH_Unlock();	//解锁
	FLASH_ProgramWord(Address, Data);	//编程字
	FLASH_Lock();	//加锁
}

void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data){	//FLASH编程半字
	FLASH_Unlock();	//解锁
	FLASH_ProgramHalfWord(Address, Data);	//编程半字
	FLASH_Lock();	//加锁
}
