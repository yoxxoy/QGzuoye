#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "Nixie.h"

void main()
{
	UART_Init();
//	UART_SendByte('B');//文本模式显示
//	UART_SendByte(0x42);//HEX模式显示
	Nixie(1,0);

	while(1)
	{
		
	}
}

void UART_Routine() interrupt 4//串口中断号
{
	 if(RI==1)//如果是接受中断
	 {
		 RI=0;//中断后软件清零		 
		 Nixie(1,SBUF);
	//串口控制LED
//		 P2=SBUF;//P2=读取中断数据
//		 UART_SendByte(SBUF);
	 }
}