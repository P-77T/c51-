
#include "time.h"


void time0_init()
{
	TMOD|=0X01;  //选择为定时器0模式，工作方式1
	TH0=(65536-10000)/256;	 //给定时器赋初值，定时10ms
	TL0=(65536-10000)%256;	
	ET0=1;       //打开定时器1中断允许 IE 2
	EA=1;        //打开总中断          IE 8
	TR0=0;      //关闭定时器           TCON 5
}

void time1_init()
{
	TMOD|=0X10;   //选择为定时器1模式，工作方式1
	TH1=(65536-10000)/256;   	//给定时器赋初值，定时10ms
	TL1=(65536-10000)%256;	
	ET1=1;       //打开定时器1中断允许 IE 4
	EA=1;        //打开总中断          IE 8
	TR1=0;      //关闭定时器           TCON 7
}

void exti0_init()	//中断方式0
{
	IT0=1;              //跳变沿触发方式（下降沿） TCON 1
	EX0=1;              //打开INT0的中断允许       IE 1
	EA=1;               //打开总中断               IE 8
}

void exti1_init()	//中断方式0
{
	IT1=1;              //跳变沿触发方式（下降沿） TCON 3
	EX1=1;              //打开INT1的中断允许       IE 3
	EA=1;               //打开总中断               IE 8
}

