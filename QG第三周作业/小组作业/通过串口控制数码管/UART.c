#include <REGX52.H>


/**
  * @brief  串口初始化，4800bps@11.0592MHz
  * @param  无
  * @retval 无
  */

void UART_Init()	
{
	SCON=0x50;			//串行控制寄存器（50接收，40发送）
	PCON |= 0x80;		//使能波特率倍速位SMOD
	
	TMOD &= 0x0F;		//配置定时器1，左边，设置定时器模式
	TMOD |= 0x20;		//0010自动重装 设置定时器模式
//波特率计算器，波特率加倍，8位数据，8位自动重装，12T
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;		//使能中断
	ES=1;		//串口中断
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */

void UART_SendByte(unsigned char Byte)//发送字节
{
	SBUF=Byte;//写入SBUF即发送
	while(TI==0);//检测是否完成（T1中断标志位，是否完成，软件清零）
	TI=0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4//串口中断号
{
	 if(RI==1)//如果是接受中断
	 {
		 
		 RI=0;//中断后软件清零
	 }
}
*/
