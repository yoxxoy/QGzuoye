#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec,i;
unsigned char Word[]={"helloword "};

void main()
{
	UART_Init();
	while(1)
	{
		for(i=0;i<sizeof(Word);i++)
		{
			UART_SendByte(Word[i]);	
		}
		Sec++;
		Delay(1000);
	}
}