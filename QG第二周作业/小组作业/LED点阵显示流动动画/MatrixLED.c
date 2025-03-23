#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;		//SRCLK
sbit SER=P3^4;		//SER

#define MATRIX_LED_PORT		P0//行控制

/**
  * @brief  74HC595写入一个字节
  * @param  Byte要写入的字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);	//后面非零即一（赋值给一位）
		SCK=1;			//上成沿移位进去
		SCK=0;			//复位做准备
	}
	RCK=1;
	RCK=0;
	//循环写法见上表
//	SER=Byte&0x80;	//后面非零即一（赋值给一位）
//	SCK=1;			//上成沿移位进去
//	SCK=0;			//复位做准备
//	SER=Byte&0x40;	//0100 0000移第二位
//	SCK=1;			
//	SCK=0;			
//	SER=Byte&0x20;	//后面非零即一（赋值给一位）
//	SCK=1;			//上成沿移位进去
//	SCK=0;			//复位做准备
	
}
	
/**
  * @brief  点阵屏初始化
  * @param  无
  * @retval 无
  */
void MatrixLED_Init()
{
	SCK=0;		//单片机复位L口都为高电频1
	RCK=0;
}

/**
  * @brief  LED点阵屏显示一列数据
  * @param  Column要选择的列，范围0~7，0在最左
  * @param  Data选择列显示的数据，高位在上，1为亮
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)//列 断码
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);//位选
	Delay(1);
	P0=0xFF;//位清零
}
