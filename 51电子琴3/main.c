#include <REGX52.H>
#include "time.h"
#include "Delay.h"
#include "LCD1602.h"


sbit key=P3^2;
sbit SOUNDER=P3^7;
unsigned char mode;

//播放速度，值为四分音符的时长(ms)
#define SPEED	500

#define P	  0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36



//频率表 C调
unsigned int FreqTable[]={0,//休止符
									//低音    1     1#    2     2#    3     4#    4#    5			5#		6			6#    7
													63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,
									//中音    1     1#    2     2#    3     4#    4#    5			5#		6			6#    7
													64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
									//高音    1     1#    2     2#    3     4#    4#    5			5#		6			6#    7
													65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,
};

unsigned char Musical_note;

/*


*/
void  electronic_play()
{ 
	
	unsigned char btn;
	
	P1 = 0xff;
	time0_init();
	while(1)
	{
		if(mode==0)          
		{
			//反转法
			
			P1 = 0xf0;						//列输入
			if(0xf0 != (P1&0xf0))  			//识别列中是否有键按下
			{
				Delay(10);				//去抖动
				if(0xf0 != (btn=P1&0xf0))	//再次识别并送列码
				{
					P1 = 0x0f;				//行输入
					btn |= (P1&0x0f);		//取行码，并与列码组合
					TR0=1;     				//
					switch(btn)				//判键值
					{						 
						case 0xee:Musical_note = M1;LCD_ShowString(1,1,"M1");break; 
						case 0xde:Musical_note = L7;LCD_ShowString(1,1,"L7");break;
						case 0xbe:Musical_note = L6;LCD_ShowString(1,1,"L6");break; 
						case 0x7e:Musical_note = L5;LCD_ShowString(1,1,"L5");break; 
						case 0xed:Musical_note = M5;LCD_ShowString(1,1,"M5");break;
						case 0xdd:Musical_note = M4;LCD_ShowString(1,1,"M4");break;
						case 0xbd:Musical_note = M3;LCD_ShowString(1,1,"M3");break;
						case 0x7d:Musical_note = M2;LCD_ShowString(1,1,"M2");break;
						case 0xeb:Musical_note = H2;LCD_ShowString(1,1,"H2");break;
						case 0xdb:Musical_note = H1;LCD_ShowString(1,1,"H1");break;
						case 0xbb:Musical_note = M7;LCD_ShowString(1,1,"M7");break;
						case 0x7b:Musical_note = M6;LCD_ShowString(1,1,"M6");break;
						case 0xe7:Musical_note = H6;LCD_ShowString(1,1,"H6");break;
						case 0xd7:Musical_note = H5;LCD_ShowString(1,1,"H5");break;
						case 0xb7:Musical_note = H4;LCD_ShowString(1,1,"H4");break;
						case 0x77:Musical_note = H3;LCD_ShowString(1,1,"H3");break;
						default:TR0 = 0;break;
					}
				}
			} 
			if(0xf0 == P1)
			{
				TR0 = 0;
				SOUNDER = 1;     //松开按键关定时器，停蜂鸣器
			}
		}
		else break;
	}
}

void T0sev() interrupt 1
{
	TH0 =  FreqTable[Musical_note]/ 256;
	TL0 =  FreqTable[Musical_note]% 256;
	SOUNDER = ~SOUNDER;		
}

//{音符,时值},一行为小节,以4作为四分音符
//天空之城 频谱
unsigned char code Music1[122][2]={
	//1
	{P,	4},{P,	4},{P,	4},{M6,	2},{M7,	2},
	{H1,	4+2},{M7,	2},{H1,	4},{H3,	4},
	{M7,	4+4+4},{M3,	2},{M3,	2},
	
	//2
	{M6,	4+2},{M5,	2},{M6, 4},{H1,	4},
	{M5,	4+4+4},{M3,	4},
	{M4,	4+2},{M3,	2},{M4,	4},{H1,	4},
	
	//3
	{M3,	4+4},{P,	2},{H1,	2},{H1,	2},{H1,	2},
	{M7,	4+2},{M4_,2},{M4_,4},{M7,	4},
	{M7,	8},{P,	4},{M6,	2},{M7,	2},
	
	//4
	{H1,	4+2},{M7,	2},{H1,	4},{H3,	4},
	{M7,	4+4+4},{M3,	2},{M3,	2},
	{M6,	4+2},{M5,	2},{M6, 4},{H1,	4},
	
	//5
	{M5,	4+4+4},{M2,	2},{M3,	2},
	{M4,	4},{H1,	2},{M7,	2+2},{H1,	2+4},
	{H2,	2},{H2,	2},{H3,	2},{H1,	2+4+4},
	
	//6
	{H1,	2},{M7,	2},{M6,	2},{M6,	2},{M7,	4},{M5_,4},
	{M6,	4+4+4},{H1,	2},{H2,	2},
	{H3,	4+2},{H2,	2},{H3,	4},{H5,	4},
	
	//7
	{H2,	4+4+4},{M5,	2},{M5,	2},
	{H1,	4+2},{M7,	2},{H1,	4},{H3,	4},
	{H3,	4+4+4+4},
	
	//8
	{M6,	2},{M7,	2},{H1,	4},{M7,	4},{H2,	2},{H2,	2},
	{H1,	4+2},{M5,	2+4+4},
	{H4,	4},{H3,	4},{H3,	4},{H1,	4},
	
	//9
	{H3,	4+4+4},{H3,	4},
	{H6,	4+4},{H5,	4},{H5,	4},
	{H3,	2},{H2,	2},{H1,	4+4},{P,	2},{H1,	2},
	
	//10
	{H2,	4},{H1,	2},{H2,	2},{H2,	4},{H5,	4},
	{H3,	4+4+4},{H3,	4},
	{H6,	4+4},{H5,	4+4},
	
	//11
	{H3,	2},{H2,	2},{H1,	4+4},{P,	2},{H1,	2},
	{H2,	4},{H1,	2},{H2,	2+4},{M7,	4},
	{M6,	4+4+4},{P,	4},
	
	0xff	//终止标志,播放完毕
};

unsigned char code Music2[][2]={
	//5
  {H5,2},{H3,1},{H4,1},{H5,2},{H3,1},{H4,1},
	{H5,1},{M5,1},{M6,1},{M7,1},{H1,1},{H2,1},{H3,1},{H4,1},
	{H3,2},{H1,1},{H2,1},{H3,2},{M3,1},{M4,1},
	{M5,1},{M6,1},{M5,1},{M4,1},{M5,1},{M3,1},{M4,1},{M5,1},	
	{M4,2},{M6,1},{M5,1},
	{M4,2},{M3,1},{M2,1},{M3,1},{M2,1},{M1,1},{M2,1},{M3,1},{M4,1},{M5,1},{M6,1},
	{M4,2},{M6,1},{M5,1},{M6,2},{M7,1},{H1,1},
	{M5,1},{M6,1},{M7,1},{H1,1},{H2,1},{H3,1},{H4,1},{H5,1},
	{H3,2},{H1,1},{H2,1},{H3,2},{H2,1},{H1,1},
	{H2,1},{M7,1},{H1,1},{H2,1},{H3,1},{H2,1},{H1,1},{M7,1},
	{H2,2},{M6,1},{M5,1},{H1,2},{M1,1},{M2,1},
	{M3,1},{M4,1},{M3,1},{M2,1},{M3,1},{H1,1},{M7,1},{H1,1},
	{H6,2},{H1,1},{M7,1},{M6,2},{M5,1},{M4,1},
	{M5,1},{M4,1},{M3,1},{M4,1},{M5,1},{M6,1},{M7,1},{H1,1},
	{H6,2},{H1,1},{M7,1},{H1,2},{M7,1},{M6,1},
	{M7,1},{H1,1},{H2,1},{H1,1},{M7,1},{H1,1},{M6,1},{M7,1},{H1,4+4},
	//6
	{H3,2},{M3,2},{M4,2},{M3,2},{M2,2},{H2,2},{H3,2},{H2,2},
	{H1,2},{M3,2},{M1,2},{M6,2},{M5,2},{M5,2},{M4,2},{M5,2},
	{M6,2},{M6,2},{M7,2},{M6,2},{M5,2},{M5,2},{M4,2},{M5,2},
	{M6,2},{M6,2},{M5,2},{M6,2},{M7,2},{M7,2},{M6,2},{M7,2},
	{H1,2},{H1,2},{M2,2},{H1,2},{M7,2},{M7,2},{H1,2},{M7,2},
	{M6,2},{M6,2},{M5,2},{M6,2},{M7,2},{M7,2},{H3,2},{H2,2},
	{H1,2},{H1,2},{H2,2},{H4,2},{H3,2},{M3,2},{M5,2},{H3,2},
	{H1,2},{M4,2},{H3,2},{H4,2},{H2,2},{H5,2},{H4,2},{H5,2},
	//7
	{H1,2},{H1,1},{H2,1},{H3,2},{H1,2},{M7,2},{H7,1},{M1,1},{H2,2},{M7,2},
	{H1,2},{M6,1},{M7,1},{H1,2},{M6,2},{M7,2},{H5,1},{H4,1},{H3,2},{H2,2},
	{H1,2},{H4,1},{H3,1},{H2,2},{H4,2},{H3,2},{H1,1},{H2,1},{H3,2},{M5,2},
	{M4,2},{M6,1},{M5,1},{M4,2},{M3,2},{M2,2},{M5,1},{M4,1},{M3,2},{M2,2},
	{M3,2},{H1,1},{M7,1},{H1,2},{M3,2},{M5,2},{M6,1},{M7,1},{H2,2},{M7,2},
	{M6,2},{H1,1},{H2,1},{H3,2},{H1,2},{H3,2},{H3,1},{H2,1},{H1,2},{M7,2},
	{M6,2},{M6,2},{M5,1},{M6,2},{M7,2},{H1,1},{H3,1},{H2,1},{H1,2},{H3,2},
	{H4,2},{H1,1},{M7,1},{M6,2},{M6,2},{M4,2},{M2,2},{M5,2},{M5,2},
	//8
	{H5,4+4+4+4+2},{H1,4+4+4+2},
	{H5,4},{H4,4+4},{H5,4+4},{H4,4},{H1,4+2},{H1,4-2},{H1,4},{M7,2},{H1,4+4},{H1,2},
	{M7,4+4},{M6,4+4},{M5,4+4},{M1,4+2},{M2,2},
	{M3,4+4},{M6,4+4},{M2,4+4},{H2,2},{H3,4+2},
	{H3,2},{H3,2},{H4,2},{H3,2},{H2,2},{H1,4},{H1,2},{H1,2},{H2,2},{H1,2},{M7,4},
	{M6,4+4},{H1,4+4},{H1,2},{M7,2},{M6,2},{M7,2},{M5,4+2},{M5,2},{M5,4+2},{M5,2},
	{M5,2},{M6,2},{M5,2},{M4,2},{M3,4+2},{H3,2},
	{H3,2},{H4,2},{H3,2},{H2,2},{H1,4},{M7,4},{M6,2},{M7,2},
	{M5,4+2},{M5,2},{M4,4},{H1,4},{M7,4+4},{H1,2},{H1,4+4},{M7,4+4},
	{M6,4+4},{M5,2},{M5,4},{M4,4+4},
	//9
	{M3,4},{M2,4+4},{P,2},{M2,2},{M3,4},{H3,4+4},{H2,4},
	{H1,4},{H1,4+4},{M7,4},{M6,4+4},{H1,4},{M5,4},
	{M6,4+4},{M5,4+4},{M5,4+4},{M5,4+2},{M4,2},{H3,4+4},{H3,4+2},{H2,2},
	{H1,4+4+4+4+4+4},{M7,4+4},{H1,4},{M1,4},{L7,4},{M7,4},{M6,4},{M6,4},{M5,4},{H5,4},
	{H4,4},{M1,4},{M3,4},{H3,4},{H2,4},{M6,4},{M2,4},{H2,4},
	{H1,4},{M1,4},{L7,4},{M7,4},{M6,4},{M6,4},{M5,4},{H5,4},
	{H4,4},{M1,4},{M3,4},{H3,4},{H4,4+4},{H5,4+4},{H1,4+4+4+4},
	
	0xff,
	/*
	{M},{M},{M},{M},{M},{M},{M},{M},
	{M,1},{M,2},{M,4},{M,4+4},{M,4+4+4},{M,4+4+4+4},
	{H,1},{H,2},{H,4},{H,4+4},{H,4+4+4},{H,4+4+4+4},*/
};
unsigned char FreqSelect,MusicSelect;

void music1_play()
{

	time1_init();
	LCD_ShowString(1,1,"Music:");
	LCD_ShowString(2,1,"Castle InThe Sky");

		while(1)
		{
	
			if(mode==1)
			{
				if(Music1[MusicSelect][0] != 0xff)	//如果不是停止标志位
				{

					FreqSelect = Music1[MusicSelect][0];	//选择音符对应的频率
					Delay(SPEED / 4*Music1[MusicSelect][1]);	//选择音符对应的时值
					MusicSelect++;
					TR1 = 0;
					Delay(5);	//音符间短暂停顿
					TR1 = 1;	
				}
				else	//如果是停止标志位
				{
					TR1 = 0;
					LCD_WriteCommand(0x01);  //清屏
					Delay(2000);
					LCD_ShowString(1,1,"Music:");
					LCD_ShowString(2,1,"Castle InThe Sky");
					MusicSelect = 0;
				}
			}
			else 
			{
				TR1 = 0;
				break;
			}
		}
}

void music2_play()
{

	time1_init();
	    //
	LCD_ShowString(1,1,"Music:");
	LCD_ShowString(2,1,"Canon");

		while(1)
		{
	
			if(mode==2)
			{
				if(Music2[MusicSelect][0] != 0xff)	//如果不是停止标志位
				{

					FreqSelect = Music2[MusicSelect][0];	//选择音符对应的频率
					Delay(SPEED / 4*Music2[MusicSelect][1]);	//选择音符对应的时值
					MusicSelect++;
					TR1 = 0;
					Delay(5);	//音符间短暂停顿
					TR1 = 1;	
				}
				else	//如果是停止标志位
				{
					TR1 = 0;
					LCD_WriteCommand(0x01);  //清屏
					Delay(2000);
					LCD_ShowString(1,1,"Music:");
					LCD_ShowString(2,1,"Canon");
					MusicSelect = 0;
				}
			}
			else 
			{
				TR1 = 0;
				break;
			}
		}
}

void T1sev() interrupt 3            //
{
	if(FreqTable[FreqSelect])	//如果不是休止符
	{
		/*取对应频率值的重装载值到定时器*/
		TH1 = FreqTable[FreqSelect]/256;		
		TL1 = FreqTable[FreqSelect]%256;		
  	SOUNDER = ~SOUNDER;	
	}
}

void exti0() interrupt 0 //外部中断0中断函数
{
	
	Delay(10);
	if(key==0)
	{
		TR0=0;
		TR1=0;             //光定时器
		mode++;
		LCD_Init();
		if(mode==3)
			mode=0;
	}
}

void main()
{
	LCD_Init();
	mode = 0x00;
	exti0_init();               //外部中断0配置
	while(1)
	{
		
		if(mode==1)
			music1_play();
		else if(mode==2)
			music2_play();
		else if(mode==0)
			electronic_play();
		
	}	
	
}