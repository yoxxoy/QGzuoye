#include <REGX52.H>
#include "Key.h"
#include "Delay.h"


unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//定义单个数码管显示数字

void Nixie(unsigned char Location,Number)
{
	switch(Location)//定义三个银脚选择第几个数码管
	{	
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];
	Delay(1);
	P0=0x00;
}


unsigned int a=0,b=0,Keynum;
void main()
{	
	while(1)
	{
		Nixie(1,a);
		Nixie(2,b);
		Keynum=Key();
		if(Keynum==1)
		{
			if(b==9)
			{
				a++;
				b=0;
			}
			else
			{
				++b;
			}
			Delay(1);
		}
		
	}



}