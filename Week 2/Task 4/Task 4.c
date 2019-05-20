#include<reg52.h>
#include<math.h>
typedef unsigned int ui;
typedef unsigned char uc;
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit led4=P2^4;
sbit led5=P2^5;
sbit led6=P2^6;
sbit led7=P2^7;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

	char code du[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	                                     0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

 void delay(unsigned int i)   //i=1 10us
{
	while(i--);
}

void we(char i)   //??0~7
{
	switch(i)
	{
		case 0:LSA=0,LSB=0,LSC=0;break;
		case 1:LSA=1,LSB=0,LSC=0;break;
		case 2:LSA=0,LSB=1,LSC=0;break;
		case 3:LSA=1,LSB=1,LSC=0;break;
		case 4:LSA=0,LSB=0,LSC=1;break;
		case 5:LSA=1,LSB=0,LSC=1;break;
		case 6:LSA=0,LSB=1,LSC=1;break;
		case 7:LSA=1,LSB=1,LSC=1;
	}
}

void see(int i,char j)
{
	   we(j);
	    i=i/pow(10,j);
	   P0=i%10;
  
}
static bit z=0;
void display(int i)
{
	if(i<=9)
	{
		we(0);
		P0=du[i];

		
	}
	if(i>9&&i<21)
	{
		char k=30;
		while(k)
		{
		 we(0);
		P0=du[i%10];
		delay(100);
		P0=0;
    we(1);
		P0=du[i/10];
		delay(100);
		P0=0;
			k--;
		}
	}
		
}
void timer0()    
{
	TMOD=0X01;
	TH0=0XFC;
	TL0=0X18;	     // 1ms
	ET0=1;
	EA=1;
	TR0=1;	
}

static int keynum ;
void key()
{

	char a=0;
	P1=0x0f;
	if(P1!=0x0f)//读取按键是否按下
	{
		delay(1000);//延时10ms进行消抖
		if(P1!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			P1=0X0F;
			switch(P1)
			{
				case(0X07):	keynum=0;break;
				case(0X0b):	keynum=1;break;
				case(0X0d): keynum=2;break;
				case(0X0e):	keynum=3;break;
			}
			//测试行
			P1=0XF0;
			switch(P1)
			{
				case(0X70):	keynum=keynum;break;
				case(0Xb0): keynum=keynum+4;break;
				case(0Xd0): keynum=keynum+8;break;
				case(0Xe0):	keynum=keynum+12;break;
			}
			while((a<50)&&(P1!=0xf0))	 //检测按键松手检测
			{
				delay(1000);
				a++;
			}
		}
	}
}



static i=0,t=0,h=0;      //static   
//main function

void main()
{
	timer0();
	E:;
	keynum=9;
	t=0;
	we(0);
	P0=du[0];
	while(1)
	{
	key();
		if(keynum==0) 
		{
			keynum=9;
			if(t!=20)
				t++;
			else
				t=20;
		}
		if(keynum==1)
		{
			keynum=9;
			 if(t!=0)
				t--;
			 else
				t=0;
		 }
		if(keynum==2) 
		{
			keynum=9;
			goto E;
		}
	 }
 }
	 void exit() interrupt 1
	 { 
	
	
		   display(t);
		 
	 }
	
	