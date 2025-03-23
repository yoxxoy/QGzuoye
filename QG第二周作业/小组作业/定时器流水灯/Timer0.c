#include <REGX52.H>


/**
  * @brief  定时器0初始化，1毫秒
  * @param  无
  * @retval 无
  */
//TMOD高四位定时器1，低四位定时器0，分别为GATE C/T （M1 M0共同代表模式）
void Timer0Init(void)
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

//	TMOD=0x01;		//0000 0001
//	TMOD=TMOD&0xF0; //把代码低四位清零，高四位不变（原理和1111 0000按位与，高四位是啥为啥）
//	TMOD=TMOD|0x01; //把代码最低位置1，高四位不变 （原理和0000 0001按位与，低四位有1为1）
//	//TCON配置
//	TF0=0;			//程序溢出中断位
//	TR0=1;			//计时器开始工作
//	TH0=64535/256;	//二进制，取出前八位
//	TL0=64535%256;	//低8位，二者合一起为1000us,1ms
	//下面要自己配置
	ET0=1;
	EA=1;
	PT0=0;
}

/*
定时器中断函数模板

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;

	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
		
	}
}
*/