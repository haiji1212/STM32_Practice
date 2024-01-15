#include "stm32f10x.h"
#include "myi2c.h"
#include "mpu6050_reg.h"

#define MPU6050_ADDRESS		0xD0	//1101 000 0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){	//写寄存器
	MyI2C_Start();	//I2C起始
	MyI2C_SendByte(MPU6050_ADDRESS);	//发送从机地址，读写位为0
	MyI2C_ReceiveAck();	//接收应答
	MyI2C_SendByte(RegAddress);	//发送寄存器地址
	MyI2C_ReceiveAck();	//接收应答
	MyI2C_SendByte(Data);	//发送数据
	MyI2C_ReceiveAck();	//接收应答
	MyI2C_Stop();	//I2C终止
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){	//读寄存器
	uint8_t Data;
	
	MyI2C_Start();	//I2C起始
	MyI2C_SendByte(MPU6050_ADDRESS);	//发送从机地址，读写位为0
	MyI2C_ReceiveAck();	//接收应答
	MyI2C_SendByte(RegAddress);	//发送寄存器地址
	MyI2C_ReceiveAck();	//接收应答
	
	MyI2C_Start();	//I2C重复起始
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	//发送从机地址，读写位为1
	MyI2C_ReceiveAck();	//接收应答
	Data = MyI2C_ReceiveByte();	//接收数据
	MyI2C_SendAck(1);	//发送应答，给从机非应答，终止从机的数据输出
	MyI2C_Stop();	//I2C终止
	
	return Data;
}

void MPU6050_Init(void){
	MyI2C_Init();	//I2C初始化
	/*MPU6050寄存器初始化，需要对照MPU6050手册的寄存器描述配置，此处仅配置了部分重要的寄存器*/
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);	//电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);	//电源管理寄存器2，保持默认值0，所有轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);	//采样率分频寄存器，配置采样率
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);	//配置寄存器，配置DLPF
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g
}

uint8_t MPU6050_GetID(void){	//MPU6050获取ID号
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);	//返回WHO_AM_I寄存器的值
}

/**
  * 函    数：MPU6050获取数据
  * 参    数：AccX AccY AccZ 加速度计X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 参    数：GyroX GyroY GyroZ 陀螺仪X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 返 回 值：无
  */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ){
	uint8_t DataH, DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
