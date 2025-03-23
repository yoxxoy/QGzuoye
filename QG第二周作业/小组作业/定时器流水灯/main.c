#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum=0,LEDMode;
void main()
{
	P2=0xFE;//点亮最低位LED
	Timer0Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				LEDMode++;
				if(LEDMode>=2)LEDMode=0;
			}
			
		}
	}
}




void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	//定时器中断
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0count++;
	if(T0count>=500)
	{
		T0count=0;
		if(LEDMode==0)
			P2=_crol_(P2,1);
		if(LEDMode==1)
			P2=_cror_(P2,1);
		
		
	}
}